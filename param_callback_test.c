/**
 * param_callback_test.c : Test parameter change callback notification
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("hi");
MODULE_VERSION("1.0");
MODULE_DESCRIPTION("Test parameter change callback notification");

static int val, arr_val[4];
static char* name;

static int val_cb=0;

module_param(val, int, S_IRUSR | S_IWUSR);
MODULE_PARM_DESC(val, "An integer");

module_param(name, charp, S_IRUSR | S_IWUSR);
MODULE_PARM_DESC(name, "A character string");

module_param_array(arr_val, int, NULL, S_IRUSR | S_IWUSR);
MODULE_PARM_DESC(arr_val, "An array of integers");

int notify_param (const char *val, const struct kernel_param *kp){
    int res = param_set_int(val,kp);
    if(res==0){
        pr_info("Callback function called....");
        pr_info("New value of val_cb = %d \n", val_cb);
        return 0;
    }
    return -1;
}

const struct kernel_param_ops cb_param_ops = {
    .set = &notify_param, //use the custom setter
    .get = &param_get_int, //use standard getter
};

module_param_cb(val_cb, &cb_param_ops, &val_cb, S_IRUGO | S_IWUSR);

static int __init param_callback_init(void){
    int i;
    pr_info("val = %d \n", val);
    pr_info("val_cb = %d \n", val_cb);
    pr_info("name = %s \n", name);
    for(i=0;i<(sizeof(arr_val)/sizeof(i));i++){
        pr_info("arr_val[%d] = %d \n", i, arr_val[i]);
    }
    pr_info("Kernel Module Inserted Successfully...\n");
    return 0;
}

void __exit param_callback_exit(void){
    pr_info("Kernel Module Removed Successfully...\n");
}

module_init(param_callback_init);
module_exit(param_callback_exit);
