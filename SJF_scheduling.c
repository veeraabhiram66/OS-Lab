#include <stdio.h>
#include <stdlib.h>


struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int finishTime;
    int turnaroundTime, waitingTime, responseTime;
    struct Process *next;
};

struct MinHeap {
    struct Process *head;
};

struct MinHeap *createMinHeap() {
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
    minHeap->head = NULL;
    return minHeap;
}

void swapProcesses(struct Process *a, struct Process *b) {
    int temp;
    temp = a->pid;
    a->pid = b->pid;
    b->pid = temp;
    temp = a->arrivalTime;
    a->arrivalTime = b->arrivalTime;
    b->arrivalTime = temp;
    temp = a->burstTime;
    a->burstTime = b->burstTime;
    b->burstTime = temp;
}

void heapify(struct Process *proc) {
    struct Process *min = proc;
    struct Process *l = proc->next;
    struct Process *r = l ? l->next : NULL;
    if (l && l->burstTime < min->burstTime) {
        min = l;
    }
    if (r && r->burstTime < min->burstTime) {
        min = r;
    }
    if (min != proc) {
        swapProcesses(min, proc);
        heapify(min);
    }
}

void insert(struct MinHeap *minHeap, struct Process *proc) {
    if (minHeap->head == NULL) {
        minHeap->head = proc;
        return;
    }
    struct Process *proc1 = (struct Process *)malloc(sizeof(struct Process));
    proc1->pid = proc->pid;
    proc1->arrivalTime = proc->arrivalTime;
    proc1->burstTime = proc->burstTime;
    proc1->next = minHeap->head;
    minHeap->head = proc1;

    struct Process *ptr = minHeap->head;
    while (ptr != NULL) {
        heapify(ptr);
        ptr = ptr->next;
    }
}

int main() {
    int numProcesses;
    printf("Enter number of processes: ");
    scanf("%d", &numProcesses);
    int processId = 0;
    int arrivalTime, burstTime;
    int prevStartTime = 0;
    struct Process *processes[numProcesses];
    struct Process *completedProcesses[numProcesses];

    for (int i = 0; i < numProcesses; i++) {
        processId++;
        printf("Enter arrival time and burst time of process %d: ", processId);
        scanf("%d %d", &arrivalTime, &burstTime);
        processes[i] = (struct Process *)malloc(sizeof(struct Process));
        processes[i]->pid = processId;
        processes[i]->arrivalTime = arrivalTime;
        processes[i]->burstTime = burstTime;
        processes[i]->next = NULL;
    }
    struct MinHeap *minHeap = createMinHeap();
    int numCompletedProcesses = 0;
    int currentTime = processes[0]->arrivalTime;
    struct Process *executingProcess;
    int remainingProcesses = numProcesses;
    float averageTAT = 0, averageWT = 0;

    while (numCompletedProcesses < numProcesses) {
        int i = 0;
        while (i < numProcesses) {
            if (processes[i]->arrivalTime <= currentTime) {
                struct Process *newProcess = (struct Process *)malloc(sizeof(struct Process));
                newProcess->pid = processes[i]->pid;
                newProcess->arrivalTime = processes[i]->arrivalTime;
                newProcess->burstTime = processes[i]->burstTime;
                insert(minHeap, newProcess);
            }
            i++;
        }
        if (minHeap->head == NULL) {
            currentTime++;
            continue;
        }
        executingProcess = minHeap->head;
        executingProcess->finishTime = currentTime + executingProcess->burstTime;
        executingProcess->turnaroundTime = executingProcess->finishTime - executingProcess->arrivalTime;
        executingProcess->waitingTime = executingProcess->turnaroundTime - executingProcess->burstTime;
        executingProcess->responseTime = executingProcess->waitingTime;
        currentTime = executingProcess->finishTime;
        averageTAT += executingProcess->turnaroundTime;
        averageWT += executingProcess->waitingTime;

        completedProcesses[executingProcess->pid - 1] = (struct Process *)malloc(sizeof(struct Process));
        completedProcesses[executingProcess->pid - 1]->pid = executingProcess->pid;
        completedProcesses[executingProcess->pid - 1]->arrivalTime = executingProcess->arrivalTime;
        completedProcesses[executingProcess->pid - 1]->burstTime = executingProcess->burstTime;
        completedProcesses[executingProcess->pid - 1]->finishTime = executingProcess->finishTime;
        completedProcesses[executingProcess->pid - 1]->turnaroundTime = executingProcess->turnaroundTime;
        completedProcesses[executingProcess->pid - 1]->waitingTime = executingProcess->waitingTime;
        completedProcesses[executingProcess->pid - 1]->responseTime = executingProcess->responseTime;

        while (minHeap->head != NULL) {
            minHeap->head = minHeap->head->next;
        }
        for (int k = 0; k < numProcesses; k++) {
            if (processes[k]->pid == executingProcess->pid) {
                for (int j = k; j < numProcesses - 1; j++) {
                    processes[j] = processes[j + 1];
                }
                numProcesses--;
            }
        }

        numCompletedProcesses++;
    }
    averageTAT /= numProcesses;
    averageWT /= numProcesses;

    printf("PID\tAT\tBT\tFT\tTAT\tWT\tRT\n");
    for (int i = 0; i < remainingProcesses; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            completedProcesses[i]->pid,
            completedProcesses[i]->arrivalTime,
            completedProcesses[i]->burstTime,
            completedProcesses[i]->finishTime,
            completedProcesses[i]->turnaroundTime,
            completedProcesses[i]->waitingTime,
            completedProcesses[i]->responseTime
        );
    }
    printf("Average TAT: %f\n", averageTAT);
    printf("Average WT: %f\n", averageWT);

    return 0;
}
