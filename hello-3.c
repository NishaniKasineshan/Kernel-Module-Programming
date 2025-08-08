/**
 * hello-3.c - Demonstrating __init, __initdata & __exit macros
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int hello3_data __initdata = 3; 

static int __init hello_3_init(void){
    pr_info("Hello World 3. \n");
    return 0;
}

static void __exit hello_3_exit(void){
    pr_info("Goodbye World 3.\n");
}

module_init(hello_3_init);
module_exit(hello_3_exit);

MODULE_LICENSE("GPL");
