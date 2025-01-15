#include <stdio.h>
#define MAX_PROCESSES 100

typedef struct
{
    int id, arrivalTime, burstTime, waitingTime, turnaroundTime, remainingTime;
} Process;

void RoundRobin(Process proc[], int n, int quantum)
{
    int currentTime = 0, completed = 0;
    int remaining[MAX_PROCESSES];

    for (int i = 0; i < n; i++)
    {
        remaining[i] = proc[i].burstTime;
    }

    while (completed != n)
    {
        for (int i = 0; i < n; i++)
        {
            if (remaining[i] > 0 && proc[i].arrivalTime <= currentTime)
            {
                if (remaining[i] > quantum)
                {
                    currentTime += quantum;
                    remaining[i] -= quantum;
                }
                else
                {
                    currentTime += remaining[i];
                    proc[i].waitingTime = currentTime - proc[i].burstTime - proc[i].arrivalTime;
                    remaining[i] = 0;
                    completed++;
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        proc[i].turnaroundTime = proc[i].burstTime + proc[i].waitingTime;
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
    int n, quantum;
    Process proc[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        proc[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d%d", &proc[i].arrivalTime, &proc[i].burstTime);
        proc[i].remainingTime = proc[i].burstTime;
    }

    printf("Enter time quantum for Round Robin: ");
    scanf("%d", &quantum);

    RoundRobin(proc, n, quantum);
    printResults(proc, n);

    return 0;
}
