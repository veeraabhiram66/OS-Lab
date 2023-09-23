//A parent process creates a child process and the child process creates a grandchild process.
// The parent creates a pipe that is shared between the parent and the child.
// The parent writes a message to the pipe and the child reads it from the pipe.
// The child creates another pipe which is shared between the child and the grandchild.
// Note that this pipe is not available to the parent and is not the same as the one shared by the parent and the child.
// The grandchild writes another message to the pipe and the child reads it from the pipe. 
//After obtaining the two messages from the pipes, the child prints the difference in lengths of the two messages.
// Moreover, each of the three processes prints the PID of its respective parent process.
// The contents of the two messages must be taken as user inputs.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

int main()
{
    int fd1[2],fd2[2];
    int pipe1,pipe2;

    pipe1 = pipe(fd1);
    //pipe2 = pipe(fd2);

    if(pipe1 == -1){
        printf("Pipe 1 failed\n");                  //checking if pipe is created or not
        return 0;
    }
    if(pipe2 == -1){
        printf("Pipe 2 failed\n");
        return 0;
    }
    //parent process creates a child process and the child process creates a grandchild process
    //parent creates a pipe that is shared between the parent and the child
    //child creates another pipe which is shared between the child and the grandchild
    //parent writes a message to the pipe and the child reads it from the pipe
    //grandchild writes another message to the pipe and the child reads it from the pipe

    int p=fork();
    if(p<0){
        printf("Error creating child process\n");
        return 0;
    }
    else if(p==0){
        //child process
        pipe2 = pipe(fd2);
        int p1=fork();
        if(p1<0){
            printf("Error creating grandchild process\n");
            return 0;
        }
        else if(p1==0){
            //grandchild process
            char msg_c[100];
            //printf("Enter message in child process: \n");
            scanf("%s",msg_c);
            close(fd2[0]);
            write(fd2[1],msg_c,100);
            close(fd2[1]);
            printf("Message received in child process:\n");
            printf("Grandchild process with pid %d\n",getpid());
        }
        else{
            //child process
            char msg_c[100];
            char msg_p[100];
            close(fd2[1]);
            read(fd2[0],msg_c,100);
            close(fd2[0]);
            printf("Message received in grandchild process: %s\n",msg_c);
            close(fd1[1]);
            read(fd1[0],msg_p,100);
            close(fd1[0]);
            printf("Message received from parent : %s\n",msg_p);
            printf("Child process with pid %d\n",getpid());
            printf("Parent process with pid %d\n",getppid());
            printf("Difference in length of messages: %ld\n",strlen(msg_c)-strlen(msg_p));
        }
    }
    else{
        //parent process
        char msg_p[100];
        printf("Enter message in parent process: \n");
        scanf("%s",msg_p);
        printf("Message received in child process: %s\n",msg_p);
        printf("Parent process with pid %d\n",getpid());
        printf("Child process with pid %d\n",p);
        close(fd1[0]);
        write(fd1[1],msg_p,100);
        close(fd1[1]);
        // printf("Message received in child process: %s\n",msg_p);
        // printf("Parent process with pid %d\n",getpid());
        // printf("Child process with pid %d\n",p);
        wait(NULL);
    }
    return 0;
}