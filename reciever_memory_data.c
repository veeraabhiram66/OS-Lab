//Write two different programs (Sender and Receiver) in C to demonstrate IPC using shared memory. Process "Sender.c" will write atleast 100 bytes of data to the shared memory and process "Receiver.c" will read from the shared memory and displays it. Then, "Receiver.c" will write atleast 100 bytes of data to the same shared memory and  "Sender.c" will read and displays it. 
//reciever code

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

//read the 100 bytes of data from shared memory and display it and then write 100 bytes of data to shared memory
#define SHMSIZE 1000

int main()
{
    int shmid; key_t key; char *shm, *s;
    key = 6969;

    if((shmid = shmget(key, SHMSIZE, 0666)) < 0)
    {
        printf(" Error in shmget");
        exit(1);
    }
    if((shm = shmat(shmid, NULL, 0)) == (char *)-1)
    {
        printf(" Error in shmat");
        exit(1);
    }
    //for reading 100 bytes of data from shared memory
    for(s = shm; *s != '\0'; s++)
    {
        putchar(*s);
    }
    putchar('\n');
    //for writing 100 bytes of data to shared memory
    s = shm;
    char *msg="This message is from reciever and the message is: ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    for(int i = 0; i < strlen(msg); i++)
    {
        *s++ = msg[i];
    }
    *shm ='#';
    exit(0);
    return 0;
}