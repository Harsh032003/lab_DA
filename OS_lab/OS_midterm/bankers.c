#include <stdio.h>
#include <stdlib.h>

void calculateNeed(int process, int resources, int allocation[][resources], int max[][resources], int need[][resources])
{
    for (int i = 0; i < process; i++)
    {
        for (int j = 0; j < resources; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

int isSafe(int process, int resources, int available[], int max[][resources], int allocation[][resources], int need[][resources])
{
    int work[resources];
    int finish[process];

    int safeSequence[process];
    int count = 0;

    for (int i = 0; i < resources; i++)
    {
        work[i] = available[i];
    }

    for (int i = 0; i < resources; i++)
    {
        finish[i] = 0;
    }

    while (count < process)
    {
        int found = 0;
        for (int i = 0; i < process; i++)
        {
            if (finish[i] == 0)
            {
                int j;
                for (j = 0; j < resources; j++)
                {
                    if (need[i][j] > work[i])
                    {
                        break;
                    }
                }

                if (j == resources)
                {
                    for (int k = 0; k < resources; k++)
                    {
                        work[k] += allocation[i][k];
                    }
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0)
        {
            printf("System is not in safe state\n");
            return 0;
        }
    }

    printf("The system is in safe state\nSafe Sequence: ");
    for (int i = 0; i < process; i++)
    {
        printf("%d", safeSequence[i]);
    }

    return 1;
}

int main()
{
    int process, resources;
    printf("Enter the processes : ");
    scanf("%d", &process);

    printf("Enter the no of resources : ");
    scanf("%d", &resources);

    int allocation[process][resources];
    int max[process][resources];
    int need[process][resources];
    int available[resources];

    printf("Enter the allocation matrix : \n");
    for (int i = 0; i < process; i++)
    {
        for (int j = 0; j < resources; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }
    printf("Enter the Maximum matrix : \n");
    for (int i = 0; i < process; i++)
    {
        for (int j = 0; j < resources; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the available resource array : ");
    for (int i = 0; i < resources; i++)
    {
        scanf("%d", &available[i]);
    }

    calculateNeed(process, resources, allocation, max, need);
    isSafe(process, resources, available, max, allocation, need);

    return 0;
}