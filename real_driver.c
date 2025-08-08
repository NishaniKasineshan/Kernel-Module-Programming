/**
 * real_driver.c :  send data to kernel using write functio
 *                  store data in kernel space
 *                  when read, send the data to user space application [written by write function]  
 *                             
 *                               device file
 *       user space application <============> kernel space program
 */

//kmalloc function : used to allocate memory in kernel space ---linux/slab.h---
//                   similar to malloc in user space
//                   allocated region is contagious in physical memory
//kfree || free

//copy_from_user : copy a bloack of data from user space to kernel space
//                 returns no of bytes that could not be copied

/**
 * device_open : function called when opening device file
 *               use open() system call to open the device file in the userspace application
 * 
 * device_write : function called when writing data to the device file
 *                use write() system call to write data to the device file in the userspace application
 * 
 * device_read : function called when read device file
 *               use read() system call to read the data from the device file in the userspace application
 * 
 * device_release : function called when close device file
 *                  use close() system call to close the device file in the userspace application
 */

#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/version.h>

#define DEVICE_NAME "realdev"
#define mem_size 1024

static int device_open(struct inode*, struct file*);
static ssize_t device_write(struct file*, const char __user*, size_t, loff_t*);
static ssize_t device_read(struct file*, char __user*, size_t, loff_t*);
static int device_release(struct inode*, struct file*);

static struct file_operations dev_fops ={
    .open = device_open,
    .write = device_write,
    .read = device_read,
    .release = device_release,
};

static int major;
static struct class *devcls;
uint8_t *kernel_buffer;

static int __init dev_init(void){
    major = register_chrdev(0, DEVICE_NAME, &dev_fops);

    if (major<0) {
        pr_alert("Registering device failed with %d.\n", major);
        return major;
    }

    pr_info("Device assigned major number: %d.\n", major);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,4,0)
    devcls = class_create(DEVICE_NAME);
#else
    devcls = class_create(THIS_MODULE, DEVICE_NAME);
#endif
    
    device_create(devcls, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);
    pr_info("Device created on /dev/%s\n", DEVICE_NAME);
    return 0;
}

static void __exit dev_exit(void){
    device_destroy(devcls, MKDEV(major, 0));
    class_destroy(devcls);
    unregister_chrdev(major, DEVICE_NAME);
}

static int device_open(struct inode* inode, struct file* file){
    //allocate kernel memory
    if((kernel_buffer = kmalloc(mem_size, GFP_KERNEL))==0){
        pr_info("Cannot allocate memory in kernel\n");
        return -1;
    }
    pr_info("Device File Opened...!!!\n");
    return 0;
}

static ssize_t device_write(struct file* filp, const char __user* buf, size_t len, loff_t*off){
    //copy data from user space
    if( copy_from_user(kernel_buffer, buf, len)){
        pr_err("Data Write : Err!\n");
    }
    pr_info("Data Write:Done\n");
    return len;
}

static ssize_t device_read(struct file* filp, char __user* buf, size_t len, loff_t* off){
    //copy data to user space
    if( copy_to_user(buf, kernel_buffer, mem_size)){
        pr_err("Data Read : Err!\n");
    }
    pr_info("Data Read:Done\n");
    return mem_size;
}

static int device_release(struct inode* inode, struct file* file){
    //free allocated memory
    kfree(kernel_buffer);
    pr_info("Device File Closed...!!!\n");
    return 0;
}

module_init(dev_init);
module_exit(dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nishani");
MODULE_DESCRIPTION("A real device driver: user space <==> kernel space");
