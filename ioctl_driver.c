/***
 * ioctl_driver.c 
 */

//define ioctl command in driver.

#include <linux/ioctl.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/version.h>

#define DEVICE_NAME "ioctldev"

#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)

static int device_open(struct inode*, struct file*);
static ssize_t device_write(struct file*, const char __user*, size_t, loff_t*);
static ssize_t device_read(struct file*, char __user*, size_t, loff_t*);
static int device_release(struct inode*, struct file*);
//write ioctl function in the driver
static long  device_ioctl(struct file *,unsigned int,unsigned long);

static struct file_operations dev_fops ={
    .open = device_open,
    .write = device_write,
    .read = device_read,
    .unlocked_ioctl = device_ioctl,
    .release = device_release,
};

static int major;
static struct class *devcls;
int32_t value=0;

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
    pr_info("Device File Opened...!!!\n");
    return 0;
}

static ssize_t device_write(struct file* filp, const char __user* buf, size_t len, loff_t*off){
    pr_info("Data Write:Done\n");
    return len;
}

static ssize_t device_read(struct file* filp, char __user* buf, size_t len, loff_t* off){
    pr_info("Data Read:Done\n");
    return len;
}

static int device_release(struct inode* inode, struct file* file){
    pr_info("Device File Closed...!!!\n");
    return 0;
}

static long  device_ioctl(struct file *file,unsigned int cmd,unsigned long arg){
    switch(cmd){
        case WR_VALUE:
            if(copy_from_user(&value, (int32_t *) arg, sizeof(value))){
                pr_err("Data Write : Err!\n");
            }

            pr_info("Value = %d\n", value);
            break;
        case RD_VALUE:
            if(copy_to_user((int32_t *) arg, &value, sizeof(value))){
                pr_err("Data Read : Err!\n");
            }
            pr_info("Value Read:Done\n");
            break;
        default:
            pr_info("Default\n");
            break;
    }
    return 0;
}

module_init(dev_init);
module_exit(dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nishani");
MODULE_DESCRIPTION("IOCTL device driver: user space <==> kernel space");
