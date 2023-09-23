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

struct my_msg                       //message structure
{
    long int my_msg_type;
    int numbers[256];            //array to store the numbers
};
int main()
{
    int running = 1;              //variable to run the loop
    int msgid;                     //message id
    struct my_msg data;
    long int msg_to_receive = 0;

    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);         //create a message queue

    if(msgid == -1){
        fprintf(stderr, "msgget failed with error\n");         //error message
        exit(0);
    }

    while(running)                      //run the loop until the message queue is empty
    {
        if(msgrcv(msgid, (void *)&data, sizeof(data), msg_to_receive, 0) == -1)  //receive the message from the queue
        {
            fprintf(stderr, "msgrcv failed with error\n");
            exit(0);
        }

        int i = 0;
        int count = 0;           //count variable to count the number of odd numbers
        int oddnumbers[256];
        printf("The odd numbers are: \n");
        while(data.numbers[i] != '\0') //check till end of the array
        {
            if(data.numbers[i] % 2 != 0)      //check if the number is odd
            {
                count++;
                printf("%d ", data.numbers[i]);           //print the odd number
            }
            i++;
        }
        printf("\nNumber of odd numbers: %d\n", count);     //print the number of odd numbers
        printf("\n");
    }
       msgctl(msgid, IPC_RMID, 0);                   //remove the message queue
}