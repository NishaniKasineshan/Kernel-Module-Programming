/**
 * start.c - Modules spanning multiple files
 */

#include <linux/module.h>
#include <linux/kernel.h>

int init_module(void){
    pr_info("Hello, world - kernel start......\n");
    return 0;
}

MODULE_LICENSE("GPL");
