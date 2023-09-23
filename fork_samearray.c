/*
Roll.No:CS21B2026
Name:P.Veera Abhiram
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>


void child_array(int n, int arr[n])       //Child process
{
    int max=arr[0];
    for(int i=0;i<n;++i)               //Adding 2 to each element
    {
        arr[i]=arr[i]+2;
    }
    printf("Child process array after adding 2 to each element:\n");
    for(int i=0;i<n;++i)       //Printing the array
    {
        printf("%d\n",arr[i]);
    }
    printf("The address of the elements in the Child array are:\n");
    for(int i=0;i<n;++i)
    {
        printf("%p\n", &arr[i]);      //Printing the address of the elements
    }
    for(int i=0;i<n;++i)             //Finding the maximum element
    {
        if(arr[i]>max){
            max=arr[i];
        }
        else{
            max=max;
        }
    }
    printf("The maximum element in the Child array is %d \n", max);
}

void parent_array(int n, int arr[n])         //Parent process
{
    int min=arr[0];
    for(int i=0;i<n;++i)                 //Subtracting 3 from each element
    {
        arr[i]=arr[i]-3;
    }
    printf("Parent process array after Subtracting 3 from each element:\n");
    for(int i=0;i<n;++i)
    {
        printf("%d\n",arr[i]);       //Printing the array
    } 
    printf("The address of the elements in the Child array are:\n");
    for(int i=0;i<n;++i)
    {
        printf("%p\n", &arr[i]);    //Printing the address of the elements
    }
    for(int i=0;i<n;++i)                  //Finding the minimum element
    { 
        if(arr[i]<min){
            min=arr[i];
        }
        else{
            min=min;
        }
    }
    printf("The minimum element in the Child array is %d \n", min);
}

int main(){
    int n;
    printf("Enter the size of the array: \n");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the array elements: \n");
    for(int i=0;i<n;++i)
    {
        scanf("%d", &arr[i]);           //Taking the array elements as input
    }
    int pid = fork();                            //Creating a child process

    if(pid<0){                                         //Error
        printf("Error\n");
    }
    else if(pid==0){                                   //Child process
        printf("Child process created!\n");
        child_array(n,arr);
        printf("The process id of the process is %d and process id of Parent process is %d \n", getpid(), getppid());
    }
    else{                                             //Parent process
        printf("Parent process created!\n");
        parent_array(n,arr);
        printf("The process id of the process is %d and process id of Parent process is %d \n", getpid(), getppid());
    }
    return 0;
}