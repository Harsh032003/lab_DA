#include <stdio.h>

#define MAX_PROCESSES 10

typedef struct
{
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;

} Process;

void FCFS(Process proc[], int n)
{
    int currentTime = 0;
    for (int i = 0; i < n; ++i)
    {
        if (currentTime < proc[i].arrivalTime)
            currentTime = proc[i].arrivalTime;
        proc[i].completionTime = currentTime + proc[i].burstTime;
        proc[i].turnAroundTime = proc[i].completionTime - proc[i].arrivalTime;
        proc[i].waitingTime = proc[i].turnAroundTime - proc[i].burstTime;
        currentTime = proc[i].completionTime;
    }
}

void sortByArrivalTime(Process proc[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (proc[j].arrivalTime > proc[j + 1].arrivalTime)
            {
                Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

void printResults(Process proc[], int n)
{
    printf("\nProcess\tArrival\tBurst\tWait\tTurnaround\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n", proc[i].id, proc[i].arrivalTime, proc[i].burstTime,
               proc[i].waitingTime, proc[i].turnAroundTime);
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
    sortByArrivalTime(proc, n);
    FCFS(proc, n);
    printResults(proc, n);

    return 0;
}