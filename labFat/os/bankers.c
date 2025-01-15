#include <stdio.h>
#include <stdlib.h>

int isSafe(int processes, int resources, int available[], int max[][resources], int allocation[][resources], int need[][resources])
{
    int work[resources], finish[processes], safeSequence[processes];
    int count = 0;

    for (int i = 0; i < resources; i++)
        work[i] = available[i];

    for (int i = 0; i < processes; i++)
        finish[i] = 0;

    while (count < processes)
    {
        int found = 0;
        for (int i = 0; i < processes; i++)
        {
            if (finish[i] == 0)
            {
                int j;
                for (j = 0; j < resources; j++)
                {
                    if (need[i][j] > work[j])
                        break;
                }

                // If all resources for process i can be allocated
                if (j == resources)
                {
                    for (int k = 0; k < resources; k++)
                        work[k] += allocation[i][k];

                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0)
        {
            printf("The system is not in a safe state.\n");
            return 0;
        }
    }

    printf("The system is in a safe state.\nSafe Sequence: ");
    for (int i = 0; i < processes; i++)
        printf("%d ", safeSequence[i]);
    printf("\n");

    return 1;
}

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

int main()
{
    int processes, resources;

    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resource types: ");
    scanf("%d", &resources);

    int allocation[processes][resources], max[processes][resources], need[processes][resources], available[resources];

    printf("Enter the Allocation Matrix:\n");
    for (int i = 0; i < processes; i++)
    {
        for (int j = 0; j < resources; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the Maximum Matrix:\n");
    for (int i = 0; i < processes; i++)
    {
        for (int j = 0; j < resources; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the Available Resources Array:\n");
    for (int i = 0; i < resources; i++)
    {
        scanf("%d", &available[i]);
    }

    calculateNeed(processes, resources, max, allocation, need);

    isSafe(processes, resources, available, max, allocation, need);

    return 0;
}
