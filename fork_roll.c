/*
Roll.No:CS21B2026
Name:P.Veera Abhiram
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void child()
{
    printf("Process id: %d\n", getpid());
    printf("Parent process id: %d\n", getppid());
    printf("Returned value of fork(): %d\n", fork());
    char *file = "./program32";
    execl(file, file, NULL);
    printf("Child process exit!\n");
}

void parent()
{
    printf("Name: P.Veera Abhiram\n");
    printf("Roll number: CS21B2026\n");
    printf("Institution name: IIITDM\n");

    printf("Process id: %d\n", getpid());
    printf("Parent process id: %d\n", getppid());
    printf("Returned value of fork(): %d\n", fork());
    wait(NULL);
    printf("Parent process exit!\n");
}

int main()
{
    int pid = fork();

    if(pid < 0){
        printf("Error\n");
    }
    else if(pid == 0){
        printf("Child process started:\n");
        child();
    }
    else{
        printf("Parent process started:\n");
        parent();
    }
    return 0;
}