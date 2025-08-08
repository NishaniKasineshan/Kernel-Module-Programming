/**
 * hello-5.c - Command line argument passing to a module
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

static short myShort = 1;
static int myInt = 420;
static long myLong = 9999;
static char *myString = "blah";
static int myIntArray[2] = {420, 420};
static int arr_argc = 0;

module_param(myShort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP );
MODULE_PARM_DESC(myShort, "A short integer");

module_param(myInt, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myInt, "An integer");

module_param(myLong, long,  S_IRUSR);
MODULE_PARM_DESC(myLong, "A long integer");

module_param(myString, charp, 0000);
MODULE_PARM_DESC(myString, "A character string");

module_param_array(myIntArray, int, &arr_argc, 0000);
MODULE_PARM_DESC(myIntArray, "An array of integers");

static int __init hello_5_init(void){
    pr_info("Hello World 5.\n");
    pr_info("myShort: %hd\n", myShort);
    pr_info("myInt: %d\n", myInt);
    pr_info("myLong: %ld\n", myLong);
    pr_info("myString: %s\n", myString);

    int i=0;
    for(i=0; i<ARRAY_SIZE(myIntArray); i++){
        pr_info("myIntArray[%d] = %d\n", i, myIntArray[i]);
    }
    pr_info("got %d arguments for myIntArray.\n", arr_argc);
    return 0;
}

static void __exit hello_5_exit(void){
    pr_info("Goodbye World 5.\n");
}

module_init(hello_5_init);
module_exit(hello_5_exit);
