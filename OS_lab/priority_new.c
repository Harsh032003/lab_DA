#include <stdio.h>
#include <limits.h>

#define MAX_PROCESSES 100

typedef struct
{
    int id, arrivalTime, burstTime, waitingTime, turnaroundTime, priority;
} Process;

void PriorityScheduling(Process proc[], int n)
{
    int completed = 0, currentTime = 0;
    int isCompleted[MAX_PROCESSES] = {0};

    while (completed != n)
    {
        int minPriority = INT_MAX;
        int highest = -1;

        for (int i = 0; i < n; i++)
        {
            if (proc[i].arrivalTime <= currentTime && !isCompleted[i] && proc[i].priority < minPriority)
            {
                minPriority = proc[i].priority;
                highest = i;
            }
        }

        if (highest == -1)
        { // No process is available to execute
            currentTime++;
            continue;
        }

        currentTime += proc[highest].burstTime;
        proc[highest].waitingTime = currentTime - proc[highest].arrivalTime - proc[highest].burstTime;
        proc[highest].turnaroundTime = proc[highest].waitingTime + proc[highest].burstTime;
        isCompleted[highest] = 1;
        completed++;
    }
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
    Process proc[MAX_PROCESSES];

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
