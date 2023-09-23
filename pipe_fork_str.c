/*
Roll.No:CS21B2026
Name:P.Veera Abhiram
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){

    int fd1[2],fd2[2];

    char str[100];
    int pipe1,pipe2;

    pipe1 = pipe(fd1);
    pipe2 = pipe(fd2);

    if(pipe1 == -1){
        printf("Pipe 1 failed\n");                  //checking if pipe is created or not
        return 0;
    }
    if(pipe2 == -1){
        printf("Pipe 2 failed\n");
        return 0;
    }
    printf("Enter the string: ");
    scanf("%s",str);
    
    int p=fork();                  
    if(p<0){
        printf("Error creating child process\n");
        return 0;
    }
    else if(p==0)                    //child process
    {
        close(fd1[1]);                      //closing write end of pipe1    
        close(fd2[0]);
        char str1[100];
        read(fd1[0],str1,100);   //reading from pipe1 and storing in str1
        int i=0;
        int j=strlen(str1)-1;
        for(i=0;i<j;i++)      //reversing the string
        { 
            char temp = str1[i];
            str1[i] = str1[j];
            str1[j] = temp;
            j--;
        }
        close(fd1[0]);         
        close(fd2[0]);
        write(fd2[1],str1,100); //writing to pipe2
        close (fd2[1]);
    }
    else                           //parent process
    {
        char str1[100];
        close(fd1[0]);          //closing read end of pipe1
        write(fd1[1],str,100); //writing to pipe1
        close(fd1[1]);

        close(fd2[1]);
        read(fd2[0],str1,100);           //reading from pipe2 and storing in str1
        wait(NULL);
        printf("Reversed string sent from child process: %s\n",str1);
        close(fd2[0]);               //closing read end of pipe2
    }
    return 0;
}