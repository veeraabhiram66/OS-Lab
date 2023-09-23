/*
Name:P.Veera Abhiram
Roll.no:CS21B2026
*/
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

struct node
{
    int P_id;
    int arr_time;
    int burst_time;
    int finish_time;
    int tat;
    int wait_time;
    int res_time;
    struct node *next;
};

struct node *head = NULL;
struct node *tail = NULL;

void enqueue(int P_id, int arr_time, int burst_time)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->P_id = P_id;
    newnode->arr_time = arr_time;
    newnode->burst_time = burst_time;
    newnode->finish_time = 0;
    newnode->tat = 0;
    newnode->wait_time = 0;
    newnode->res_time = 0;
    newnode->next = NULL;
    if (head == NULL)
    {
        head = newnode;
        tail = newnode;
    }
    else
    {
        tail->next = newnode;
        tail = newnode;
    }
}

void dequeue()
{
    struct node *temp = head;
    head = head->next;
    free(temp);
}

void display()
{
    struct node *temp = head;
    while (temp != NULL)
    {
        printf("%d %d %d\n", temp->P_id, temp->arr_time, temp->burst_time);
        temp = temp->next;
    }
}

void FCFS()
{
    struct node *temp = head;
    int time = 0;
    while (temp != NULL)
    {
        if (temp->arr_time > time)
        {
            time = temp->arr_time;
        }
        temp->finish_time = time + temp->burst_time;
        temp->tat = temp->finish_time - temp->arr_time;
        temp->wait_time = temp->tat - temp->burst_time;
        temp->res_time = temp->wait_time;
        time = temp->finish_time;
        temp = temp->next;
    }
}

void sores_time()
{
    struct node *temp = head;
    struct node *temp1 = head;
    while (temp != NULL)
    {
        temp1 = temp->next;
        while (temp1 != NULL)
        {
            if (temp->arr_time > temp1->arr_time)
            {
                int P_id = temp->P_id;
                int arr_time = temp->arr_time;
                int burst_time = temp->burst_time;
                temp->P_id = temp1->P_id;
                temp->arr_time = temp1->arr_time;
                temp->burst_time = temp1->burst_time;
                temp1->P_id = P_id;
                temp1->arr_time = arr_time;
                temp1->burst_time = burst_time;
            }
            temp1 = temp1->next;
        }
        temp = temp->next;
    }
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int P_id, arr_time, burst_time;
        printf("Enter the process id:\n ");
        scanf("%d", &P_id);
        printf("Enter the arrival time:\n ");
        scanf("%d", &arr_time);
        printf("Enter the burst time:\n ");
        scanf("%d", &burst_time);
        enqueue(P_id, arr_time, burst_time);
    }
    sores_time();
    FCFS();
    printf("P_id\tAT\tBT\tFT\tTAT\tWT\tRT\n");
    struct node *temp = head;
    while (temp != NULL)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", temp->P_id, temp->arr_time, temp->
        burst_time, temp->finish_time, temp->tat, temp->wait_time, temp->res_time);
        temp = temp->next;
    }
    float avgwait_time = 0, avgtat = 0;
    temp = head;
    while (temp != NULL)
    {
        avgwait_time = avgwait_time+temp->wait_time;
        avgtat = avgtat+temp->tat;
        temp = temp->next;
    }
    avgwait_time =avgwait_time/n;
    avgtat =avgtat/n;
    printf("Average waiting time: %f\n", avgwait_time);
    printf("Average turnaround time: %f\n", avgtat);
    
    return(0);
}