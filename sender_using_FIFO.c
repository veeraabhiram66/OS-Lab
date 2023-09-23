/*
Roll.No:CS21B2026
Name : P.Veera Abhiram
*/
// Sender.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main()
{   
    int fd;
    char * myfifo = "/tmp/myfifo";          //fifo file name
    mkfifo(myfifo, 0666);                   //create a fifo file
    int a,b;                                //array to store the input
    printf("Enter a number: ");
    scanf("%d", &a);                        //read the input
    fd = open(myfifo, O_WRONLY);            //open the fifo file in write only mode
    write(fd, &a, sizeof(a));                //write the input to the fifo file
    close(fd);                              //close the fifo file
    fd = open(myfifo, O_RDONLY);            //open the fifo file in read only mode
    read(fd, &b, sizeof(b));             //read the output from the fifo file    
    close(fd);                              //close the fifo file
    printf("The one's complement of %d is %d\n", a, b); //print the one's complement
    return 0;
}
