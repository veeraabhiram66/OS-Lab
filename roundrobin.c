//  Write a C program to implement round-robin scheduling.

// (i)Take input from the user as P_id, arrival time, burst Time, and time quantum.

// (ii) Show the turnaround time, waiting time, and response time for each task.

// (iii) Compute average turnaround time, waiting time, and response time.

// (iv) Count the number of context switches (excluding the count at the beginning of the first execution process and the end of the last execution process)

// (v) Your algorithm should work for both the scenario: (a) all tasks arrive at the same time (b) tasks may arrive at a different time

// Note: You can use only integers for process id. Use the array implementation(dynamically using malloc) for the Queue. At the end of the program remove the queue from the memory.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
int front = -1;
int rear = -1;


struct process
{
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
    int completion_time;
};

//array implementation of queue
void enqueue(struct process *queue, int *front, int *rear, struct process p)
{
    if (*rear == MAX - 1)
    {
        printf("Queue is full\n");
        exit(1);
    }
    if (*front == -1)
    {
        *front = 0;
    }
    *rear = *rear + 1;
    queue[*rear] = p;
}

struct process dequeue(struct process *queue, int *front, int *rear)
{
    if (*front == -1 || *front > *rear)
    {
        printf("Queue is empty\n");
        exit(1);
    }
    struct process p = queue[*front];
    *front = *front + 1;
    return p;
}

int is_empty(int *front, int *rear)
{
    if (*front == -1 || *front > *rear)
        return 1;
    return 0;
}
//round robin scheduling
void round_robin(struct process *p, int n, int time_quantum)
{
    int front = -1, rear = -1;
    struct process *ready_queue = (struct process *)malloc(sizeof(struct process) * n);
    int current_time = 0;
    int completed = 0;
    int context_switch = 0;
    int i = 0;
    while (completed != n)
    {
        //add all the processes that have arrived till now
        while (i < n && p[i].arrival_time <= current_time)
        {
            enqueue(ready_queue, &front, &rear, p[i]);
            i++;
        }
        //if queue is empty
        if (is_empty(&front, &rear))
        {
            current_time++;
            continue;
        }
        //process the first process in the queue
        struct process p = dequeue(ready_queue, &front, &rear);
        //if process is being executed for the first time
        if (p.response_time == -1)
        {
            p.response_time = current_time - p.arrival_time;
            context_switch++;
        }
        //if process is completed
        if (p.remaining_time - time_quantum <= 0)
        {
            current_time += p.remaining_time;
            p.remaining_time = 0;
            p.completion_time = current_time;
            p.turnaround_time = p.completion_time - p.arrival_time;
            p.waiting_time = p.turnaround_time - p.burst_time;
            completed++;
        }
        //if process is not completed
        else
        {
            current_time += time_quantum;
            p.remaining_time -= time_quantum;
        }
        //add the process back to the queue if it is not completed
        if (p.remaining_time > 0)
        {
            enqueue(ready_queue, &front, &rear, p);
        }
        //if process is completed
        else
        {
            printf("Process %d completed\n", p.pid);
        }
    }
    printf("Number of context switches: %d\n", context_switch);
}




//print process list
void print_p(struct process *p, int n)
{
    printf("PID\tArrival Time\tBurst Time\tResponse Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].response_time, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }
}

int main(){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct process *p = (struct process *)malloc(sizeof(struct process) * n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter the arrival time of process %d: ", i + 1);
        scanf("%d", &p[i].arrival_time);
        printf("Enter the burst time of process %d: ", i + 1);
        scanf("%d", &p[i].burst_time);
        p[i].pid = i + 1;
        p[i].remaining_time = p[i].burst_time;
        p[i].waiting_time = 0;
        p[i].turnaround_time = 0;
        p[i].response_time = -1;
        p[i].completion_time = 0;
    }
    int time_quantum;
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);
    //calculate waiting time, turnaround time, response time, completion time
    
    round_robin(p, n, time_quantum);
    print_p(p, n);
    return 0;
}