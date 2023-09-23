/*
Roll.No:CS21B2026
Name : P.Veera Abhiram
*/
// Receiver.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


//for finding the one's complement of the input
int ones_complement(int a) {

    int b = 0, p = 1;
    while(a > 0){
        int k = a%2;
        if(k==0){
            b += p;
        }
        p *= 2;
        a /= 2;
    }
    return b;

}

int main()
{
    int fd;
    int b;
    char * myfifo = "/tmp/myfifo";          //fifo file name
    //reciever will read the input from the fifo file
    int a;                             //array to store the input
    fd = open(myfifo, O_RDONLY);            //open the fifo file in read only mode
    read(fd, &a, sizeof(a));             //read the input from the fifo file
    close(fd);                              //close the fifo file
    b = ones_complement(a);
    fd = open(myfifo, O_WRONLY);            //open the fifo file in write only mode
    write(fd, &b, sizeof(b));                //write the output to the fifo file
    close(fd);                              //close the fifo file

    return 0;

}