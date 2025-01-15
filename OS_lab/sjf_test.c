#include <stdio.h>
#include <limits.h>

#define MAX_PROCESSES 100

typedef struct
{
    int id, arrivalTime, burstTime, waitingTime, turnaroundTime;
} Process;

void SJF(Process proc[], int n)
{
    int completed = 0, currentTime = 0, minBurst = 0, shortest = 0;
    int isCompleted[MAX_PROCESSES] = {0};

    while (completed != n)
    {
        minBurst = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (proc[i].arrivalTime <= currentTime && !isCompleted[i] && proc[i].burstTime < minBurst)
            {
                minBurst = proc[i].burstTime;
                shortest = i;
            }
        }

        if (minBurst == INT_MAX)
        {
            currentTime++;
            continue;
        }

        currentTime += proc[shortest].burstTime;
        proc[shortest].waitingTime = currentTime - proc[shortest].arrivalTime - proc[shortest].burstTime;
        proc[shortest].turnaroundTime = proc[shortest].waitingTime + proc[shortest].burstTime;
        isCompleted[shortest] = 1;
        completed++;
    }
}

void printResults(Process proc[], int n)
{
    printf("\nProcess\tArrival\tBurst\tWait\tTurnaround\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n", proc[i].id, proc[i].arrivalTime, proc[i].burstTime, proc[i].waitingTime, proc[i].turnaroundTime);
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
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d%d", &proc[i].arrivalTime, &proc[i].burstTime);
    }

    SJF(proc, n);
    printResults(proc, n);

    return 0;
}
