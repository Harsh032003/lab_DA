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

} Process;

void SJF(Process proc[], int n)
{
    int completed = 0;
    int currentTime = 0;
    int minBurst = 0;
    int shortest = 0;

    int isCompleted[MAX_PROCESS] = {0};

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

        proc[shortest].waitingTime = currentTime - proc[shortest].arrivalTime;
        proc[shortest].turnaroundTime = proc[shortest].waitingTime + proc[shortest].burstTime;
        currentTime += proc[shortest].burstTime;
        completed++;
        isCompleted[shortest] = 1;
    }
}

void printResult(Process proc[], int n)
{
    printf("\nProcessID\tArrival\tBurst\tWait\tTurnaround\n");
    float wt = 0;
    float tat = 0;

    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t%d\t%d\t%d\n", proc[i].id, proc[i].arrivalTime, proc[i].burstTime, proc[i].waitingTime, proc[i].turnaroundTime);
        wt += proc[i].waitingTime;
        tat += proc[i].turnaroundTime;
    }

    printf("\nAvg wt : %.2f\nAvg tat : %.2f", wt / n, tat / n);
}

int main()
{
    int n;
    Process proc[MAX_PROCESS];

    printf("Enter the number of processes : ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        proc[i].id = i + 1;
        printf("Enter the arrival time and burst time for process %d : ", i + 1);
        scanf("%d%d", &proc[i].arrivalTime, &proc[i].burstTime);
    }

    SJF(proc, n);
    printResult(proc, n);
    return 0;
}