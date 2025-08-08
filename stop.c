/**
 * stop.c - Module spanning multiple files
 */

#include <linux/module.h>
#include <linux/kernel.h>

void cleanup_module(void){
    pr_info("Goodbye Kernel\n");
}

MODULE_LICENSE("GPL");
