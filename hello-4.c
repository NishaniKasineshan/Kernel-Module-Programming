/**
 * hello-4.c - Kernel Module Documentation
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nishani");
MODULE_DESCRIPTION("A simple driver");

static int __init hello_4_init(void){
    pr_info("Hello World 4. \n");
    return 0;
}

static void __exit hello_4_exit(void){
    pr_info("Goodbye World 4.\n");
}

module_init(hello_4_init);
module_exit(hello_4_exit);
