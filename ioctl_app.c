#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//create IOCTL command in user space application
#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)

int main(){
    int fd;
    int32_t value, number;
    printf("*********************************\n");
    fd = open("/dev/ioctldev",O_RDWR);
    if(fd<0){
        printf("Cannot open device file...\n");
        return 0;
    }

    printf("Enter the value to send to the driver: \n");
    scanf("%d",&number);
    printf("Writing value to driver\n");
    ioctl(fd, WR_VALUE, (int32_t*)&number);

    printf("Reading value from driver: \n");
    ioctl(fd, RD_VALUE, (int32_t*) &value);
    printf("Value is %d\n", value);

    printf("Closing driver\n");
    close(fd);
}