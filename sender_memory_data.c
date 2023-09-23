//Write two different programs (Sender and Receiver) in C to demonstrate IPC using shared memory. Process "Sender.c" will write atleast 100 bytes of data to the shared memory and process "Receiver.c" will read from the shared memory and displays it. Then, "Receiver.c" will write atleast 100 bytes of data to the same shared memory and  "Sender.c" will read and displays it. 
//sender code
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

//send 100 bytes of data to shared memory and recieve 100 bytes of data from shared memory and display it
#define SHMSIZE 1000
int main()
{
    char c; int shmid; key_t key; char *shm, *s;
    key = 6969;
    char *message="This is sender and the message is: abcdefghijklmnopqrstuvwxyz1234567890";
    if ((shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666)) < 0)
    {
        printf(" Error in shmget");
        exit(1);
    }
    if ((shm = shmat(shmid, NULL, 0)) == (char *)-1)
    {
        printf(" Error in shmat");
        exit(1);
    }
    s = shm;
    //for sending 100 bytes of data to shared memory
    for (int i = 0; i < strlen(message); i++)
    {
        *s++ = message[i];
    }
    *s = '\0';
    //for recieving message from shared memory
    while (*shm != '#')
    {
        sleep(1); 
    }
    for (s = shm; *s != '\0'; s++)
    {
        putchar(*s);
    }
    putchar('\n');
    exit(0);
    return 0;
}