/*
Roll.No:CS21B2026
Name:P.Veera Abhiram
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pid1, pid2, pid3, pid4;
    pid1=fork();
    if(pid1==0)                                           // creating child 1
    {
        printf("Child 1 My id is %d and my parent id is %d.\n", getpid(), getppid());     //print child 1
    }
    else if(pid1>0)                                        //return to parent
    {
        pid2=fork();
        if(pid2==0)
        {
            pid3=fork();
            if(pid3==0)                                             //creating child 3
            {
                printf("Child 3 My id is %d and my parent id is %d.\n", getpid(), getppid());      //print child 3
            }
            else if(pid3>0)                                      //return to child 2
            {
                pid4=fork();
                if(pid4==0)                                       //creating child 4
                {
                    printf("Child 4 My id is %d and my parent id is %d.\n", getpid(), getppid());  //print child 4
                }
                else if(pid4>0)                                   //return to child 2
                {
                    wait(NULL);
                    wait(NULL);
                    printf("Child 2 My id is %d and my parent id is %d.\n", getpid(), getppid());      //print child 2
                }
            }
        }
        else if(pid2>0)                                          //return to parent
        {
            wait(NULL);
            wait(NULL);
            printf("Parent Process my id is %d and my parent id is %d.\n", getpid(), getppid());     //print parent
        }
    }
    return 0;
}