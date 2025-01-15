#include <stdio.h>

// Function to calculate the need matrix
void calculateNeed(int processes, int resources, int max[][resources], int allocation[][resources], int need[][resources])
{
    for (int i = 0; i < processes; i++)
    {
        for (int j = 0; j < resources; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to detect deadlock using Banker's Algorithm
int detectDeadlock(int processes, int resources, int allocation[][resources], int need[][resources], int available[])
{
    int work[resources], finish[processes];
    int deadlockDetected = 0;

    // Initialize work and finish arrays
    for (int i = 0; i < resources; i++)
        work[i] = available[i];

    for (int i = 0; i < processes; i++)
        finish[i] = 0;

    // Try to find a process that can complete
    for (int i = 0; i < processes; i++)
    {
        if (finish[i] == 0)
        {
            int canProceed = 1;
            for (int j = 0; j < resources; j++)
            {
                if (need[i][j] > work[j])
                {
                    canProceed = 0;
                    break;
                }
            }

            if (canProceed)
            {
                for (int j = 0; j < resources; j++)
                {
                    work[j] += allocation[i][j];
                }
                finish[i] = 1;
                i = -1; // Start over to re-check all processes
            }
        }
    }

    // Check for deadlock
    printf("Processes involved in the deadlock (if any): ");
    for (int i = 0; i < processes; i++)
    {
        if (finish[i] == 0)
        {
            deadlockDetected = 1;
            printf("%d ", i);
        }
    }

    if (!deadlockDetected)
    {
        printf("None");
    }
    printf("\n");

    return deadlockDetected;
}

int main()
{
    int processes, resources;

    // Input number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resource types: ");
    scanf("%d", &resources);

    // Dynamically allocate memory for matrices and arrays
    int allocation[processes][resources], max[processes][resources], need[processes][resources], available[resources];

    // Input allocation matrix
    printf("Enter the Allocation Matrix:\n");
    for (int i = 0; i < processes; i++)
    {
        for (int j = 0; j < resources; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input maximum matrix
    printf("Enter the Maximum Matrix:\n");
    for (int i = 0; i < processes; i++)
    {
        for (int j = 0; j < resources; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    // Input available array
    printf("Enter the Available Resources Array:\n");
    for (int i = 0; i < resources; i++)
    {
        scanf("%d", &available[i]);
    }

    // Calculate the need matrix
    calculateNeed(processes, resources, max, allocation, need);

    // Check for deadlock
    int deadlock = detectDeadlock(processes, resources, allocation, need, available);

    if (deadlock)
    {
        printf("Deadlock detected!\n");
    }
    else
    {
        printf("No deadlock detected.\n");
    }

    return 0;
}
