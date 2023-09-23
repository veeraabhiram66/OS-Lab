/*
Roll.No:CS21B2026
Name:P.Veera Abhiram
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

void child_array(int n, int arr[n])          //Child process
{

    printf("The elements of the array are:\n");
    for(int i=0;i<n;++i)                              //Printing the array
    {
        printf("%d\n", arr[i]);
    }
    printf("The address of the elements in the Child array are:\n");
    for(int i=0;i<n;++i)                                 //Printing the address of the elements
    {
        printf("%p\n", &arr[i]);
    }

    printf("The elements of the array after reversing are:\n");
    for(int i=n-1;i>=0;i--)                                  //Reversing the array and printing the elements
    {
        printf("%d\n", arr[i]);
    }
    printf("The address of the elements in the Child array after reversing are:\n");
    for(int i=0;i<n;++i)                                        //Printing the address of the elements after reversing
    {
        printf("%p\n", &arr[i]);
    }
    
}

void parent_array(int n, int arr[n])                      //Parent process
{

    printf("The elements of the array are:\n");
    for(int i=0;i<n;++i)                                    //Printing the array
    {
        printf("%d\n", arr[i]);
    }
    printf("The address of the elements in the Parent array are:\n");
    for(int i=0;i<n;++i)                                        //Printing the address of the elements
    {
        printf("%p\n", &arr[i]);
    }

    printf("The elements of the array after sorting are:\n");
    for(int i=0;i<n;++i)                          //Sorting the array and printing the elements
    {
        for(int j=i+1;j<n;++j)
        {
            if(arr[i]>arr[j])
            {
                int temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }
    for(int i=0;i<n;++i)
    {
        printf("%d\n", arr[i]);
    }
    printf("The address of the elements in the Parent array after sorting are:\n");
    for(int i=0;i<n;++i)                                //Printing the address of the elements after sorting
    {
        printf("%p\n", &arr[i]);
    }
}

int main()
{
    int pid = fork();
    if(pid<0)                                                   //Error
    {
        printf("Error\n");
    }
    else if(pid==0)                                             //Child process
    {
        int n;
        printf("Enter the size of the Child array: ");
        scanf("%d", &n);
        int *arr = (int*)malloc(n*sizeof(int));                         //Dynamic memory allocation for the child array
        printf("Enter the elements of the Child array: ");
        for(int i=0;i<n;++i)                                            //input of  array elements
        {
            scanf("%d", &arr[i]);
        }
        child_array(n, arr);                                           //Calling the child function
    }
    else
    {
        wait(NULL);                                               //Parent process
        int n;
        printf("Enter the size of the Parent array: ");
        scanf("%d", &n);
        int *arr = (int*)malloc(n*sizeof(int));               //Dynamic memory allocation for the parent array
        printf("Enter the elements of the Parent array: ");
        for(int i=0;i<n;++i)                                  //input of  array elements
        {
            scanf("%d", &arr[i]);
        }
        parent_array(n, arr);                                 //Calling the parent function
    }
    return 0;
}