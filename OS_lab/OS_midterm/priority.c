#include <stdio.h>
#include <limits.h>

#define MAX_PROCESS 100

typedef struct
{
    int id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int priority;
} Process;

void priorityScheduling(Process proc[], int n)
{
}

void printResults(Process proc[], int n)
{
    printf("\nProcess\tArrival\tBurst\tPriority\tWait\tTurnaround\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", proc[i].id, proc[i].arrivalTime, proc[i].burstTime, proc[i].priority, proc[i].waitingTime, proc[i].turnaroundTime);
    }
}

int main()
{
    int n;
    Process proc[MAX_PROCESS];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        proc[i].id = i + 1;
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d%d%d", &proc[i].arrivalTime, &proc[i].burstTime, &proc[i].priority);
    }
    PriorityScheduling(proc, n);
    printResults(proc, n);

    return 0;
}