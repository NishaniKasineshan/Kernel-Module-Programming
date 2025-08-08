/**
 * hello-1.c - simple kernel module
 */

#include <linux/module.h> // Needed by all modules
#include <linux/kernel.h> // Needed for printk()

int init_module(void){

    pr_info("Hello World 1.\n");

    return 0;
}

void cleanup_module(void){

    pr_info("Goodbye World 1.\n");
}

MODULE_LICENSE("GPL");
