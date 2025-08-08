#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int8_t write_buf[1024];
int8_t read_buf[1024];

int main(){
    int fd;
    char option;
    printf("*********************************\n");
    fd = open("/dev/realdev",O_RDWR);
    if(fd<0){
        printf("Cannot open device file...\n");
        return 0;
    }

    while(1){
        printf("****Please Enter the Option******\n");
        printf("        1. Write               \n");
        printf("        2. Read                 \n");
        printf("        3. Exit                 \n");
        printf("*********************************\n");
        scanf("%c", &option);
        printf("Your option : %c\n", option);

        switch(option){
            case '1':
                printf("Enter the string to write into driver: ");
                scanf(" %[^\t\n]s", write_buf);
                printf("Data Writing..\n");
                write(fd, write_buf, strlen(write_buf)+1);
                printf("Done!\n");
                break;
            case '2':
                printf("Data Reading...\n");
                read(fd, read_buf, 1024);
                printf("Done!\n\n");
                printf("Data = %s\n\n", read_buf);
                break;
            case '3':
                close(fd);
                exit(1);
                break;
            default:
                printf("Enter Valid Option = %c\n", option);
                break;
        }       
    }
    close(fd);
}