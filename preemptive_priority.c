/*
Roll no: CS21B2026
Name: P.Veera Abhiram
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX 100
int front = -1;
int rear = -1;


struct process {
    int pid;
    int arr_time;
    int burst_time;
    int priority;
    int finish_time;
    int turn_around_time;
    int rem_time;
    int in_queue;
    int wait_time;
    int res_time;

};


void enqueue(struct process *start, struct process p){
    if(rear == MAX -1){
        printf("Queue is Full\n");
        return;
    }
    if(front == -1){
        front = 0;
    }
    rear++;
    start[rear] = p;
}

void dequeue(struct process *start){
    if(front == -1 || front > rear){
        printf("Queue is empty\n");
        return;
    }
    struct process p = start[front];
    front++;
}

int que_emp(){
    if(front == -1 || front > rear){
        return 1;
    }
    return 0;
}

void sort_process_priority(struct process *array)
{
    int i, j;
    for (i = front; i < rear; i++) {
        for (j = front; j < rear; j++) {
            if (array[j].priority > array[j + 1].priority) {
                struct process swap = array[j];
                array[j] = array[j+1];
                array[j+1] = swap;
            }
        }
    }
}

int find_process(struct process p, struct process *locate, int n){
    for(int i=0; i<n; i++){
        if(p.pid == locate[i].pid){
            return i;
        }
    }
}

void calculate(struct process *p, int n){
    for(int i=0; i<n; i++){
        p[i].turn_around_time = p[i].finish_time - p[i].arr_time;
        p[i].wait_time = p[i].turn_around_time - p[i].burst_time;
        p[i].res_time = p[i].finish_time - p[i].arr_time;
    }
}

void print_process(struct process* p, int n)
{
    printf("P_ID\tAT\tBT\tFT\tTAT\tWT\tRT\n");
    for(int i=0; i<n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arr_time, p[i].burst_time, p[i].finish_time, p[i].turn_around_time, p[i].wait_time, p[i].res_time);
    }
}


int main(){

    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct process *p=(struct process *)malloc(n * sizeof(struct process));

    for(int i=0; i<n; i++){
        printf("Enter the arrival time of process %d: ", i+1);
        scanf("%d", &p[i].arr_time);
        printf("Enter the priority of process %d: ", i+1);
        scanf("%d", &p[i].priority);
        printf("Enter the burst time of process %d: ", i+1);
        scanf("%d", &p[i].burst_time);

        p[i].pid = i+1;
        p[i].rem_time = p[i].burst_time;
        p[i].in_queue = 0;
    }

    int time = 0;
    int completed_tasks = 0;
    struct process *start = (struct process *)malloc(MAX * sizeof(struct process));
    while(completed_tasks != n){
        for(int i=0; i<n; i++){
            if(p[i].in_queue == 0 && p[i].arr_time <= time){
                enqueue(start, p[i]);
                p[i].in_queue = 1;
                sort_process_priority(start);
            }
        }
        if(que_emp()){
            time++;
            continue;
        }
        if(start[front].rem_time == 0){
            start[front].finish_time = time;
            int pos = find_process(start[front], p, n);
            p[pos].finish_time = start[front].finish_time;
            dequeue(start);
            completed_tasks++;
        }
        else{
        start[front].rem_time--;
        time++;
        }
    }
    calculate(p, n);
    print_process(p, n);
    return(0);
}
