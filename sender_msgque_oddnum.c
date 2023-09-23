/*
Roll.No:CS21b2026
Name : P.Veera Abhiram
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>

#define MAXSIZE 256                   //numbers array size

struct my_msg{
    long int my_msg_type;
    int numbers[MAXSIZE];          //array to store the numbers
};

int main()
{
int running = 1;                              //variable to run the loop
    int msgid;                               //message id
    struct my_msg data;
    char buffer[BUFSIZ];                   //buffer to store the input
    char *ptr;

    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);            //create a message queue

    if(msgid == -1){
        fprintf(stderr, "msgget failed with error\n");         //error message
        exit(0);
    }

    while(running)                               //run the loop until the message queue is empty
    {
        printf("Enter at least 10 numbers: \n");          
        fgets(buffer, BUFSIZ, stdin);         //read the input from the user and store it in buffer
        data.my_msg_type = 1;
        ptr = strtok(buffer, " ");            //split the input string into tokens
        int i = 0;
        while(ptr != NULL)
        {
            data.numbers[i] = atoi(ptr);              //convert the string to integer
            ptr = strtok(NULL, " ");                  //split the string into tokens
            i++;
        }
        if(msgsnd(msgid, (void *)&data, sizeof(data), 0) == -1)    //send the message to the queue
        {
            fprintf(stderr, "msgsnd failed\n");            //error message
            exit(0);
        }
        running = 0;

    }
    msgctl(msgid, IPC_RMID, 0);          //remove the message queue
    exit(1);
}