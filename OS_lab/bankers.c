#include <stdio.h>
#include <stdbool.h>

void calculateNeed(int n, int m, int need[n][m], int max[n][m], int allocation[n][m])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool isSafe(int n, int m, int available[m], int max[n][m], int allocation[n][m])
{
    int need[n][m];
    calculateNeed(n, m, need, max, allocation);

    bool finished[n];
    for (int i = 0; i < n; i++)
    {
        finished[i] = false;
    }

    int safeSequence[n];
    int work[m];
    for (int i = 0; i < m; i++)
    {
        work[i] = available[i];
    }

    int count = 0;
    while (count < n)
    {
        bool found = false;
        for (int p = 0; p < n; p++)
        {
            if (!finished[p])
            {
                int j;
                for (j = 0; j < m; j++)
                {
                    if (need[p][j] > work[j])
                    {
                        break;
                    }
                }

                if (j == m)
                {
                    for (int k = 0; k < m; k++)
                    {
                        work[k] += allocation[p][k];
                    }

                    safeSequence[count++] = p;
                    finished[p] = true;
                    found = true;
                }
            }
        }

        if (!found)
        {
            printf("The system is not in a safe state.\n");
            return false;
        }
    }

    printf("The system is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++)
    {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");

    return true;
}

int main()
{
    int n, m;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resource types: ");
    scanf("%d", &m);

    int available[m];
    printf("Enter the available resources:\n");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &available[i]);
    }

    int max[n][m];
    printf("Enter the maximum resources needed for each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("For process %d:\n", i);
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    int allocation[n][m];
    printf("Enter the allocated resources for each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("For process %d:\n", i);
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    isSafe(n, m, available, max, allocation);

    return 0;
}