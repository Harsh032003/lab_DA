#include <stdio.h>

#define MAX_PROCESSES 10

typedef struct
{
    int id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
} Process;

void FCFS(Process proc[], int n)
{
    int currentTime = 0;

    for (int i = 0; i < n; i++)
    {
        if (currentTime < proc[i].arrivalTime)
        {
            currentTime = proc[i].arrivalTime;
        }
        proc[i].waitingTime = currentTime - proc[i].arrivalTime;
        proc[i].completionTime = currentTime + proc[i].burstTime;
        proc[i].turnaroundTime = proc[i].waitingTime + proc[i].burstTime;
        currentTime = proc[i].completionTime;
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

    FCFS(proc, n);
    printResults(proc, n);

    return 0;
}
