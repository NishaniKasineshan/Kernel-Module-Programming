/**
 * hello-2.c - demonstrating module_init() & module_exit() macros
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h> //needed for module_init() & module_exit() macros

static int __init hello_2_init(void){
    pr_info("Hello World 2.\n");

    return 0;
}

static void __exit hello_2_exit(void){
    pr_info("Goodbye World 2.\n");
}

module_init(hello_2_init);
module_exit(hello_2_exit);

MODULE_LICENSE("GPL");
