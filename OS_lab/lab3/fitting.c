#include <stdio.h>
#include <limits.h>

#define PARTITIONS 6 // Number of memory partitions
#define PROCESSES 5  // Number of processes

// Function to implement First Fit allocation
void firstFit(int partitionSizes[], int processSizes[])
{
    int allocation[PROCESSES];
    for (int i = 0; i < PROCESSES; i++)
    {
        allocation[i] = -1; // Initialize allocation as -1 (unallocated)
    }

    for (int i = 0; i < PROCESSES; i++)
    {
        for (int j = 0; j < PARTITIONS; j++)
        {
            if (partitionSizes[j] >= processSizes[i])
            {
                allocation[i] = j;
                partitionSizes[j] -= processSizes[i]; // Reduce partition size
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < PROCESSES; i++)
    {
        if (allocation[i] != -1)
            printf("Process %d of size %d is allocated to partition %d\n", i + 1, processSizes[i], allocation[i] + 1);
        else
            printf("Process %d of size %d could not be allocated\n", i + 1, processSizes[i]);
    }
    printf("\n");
}

// Function to implement Best Fit allocation
void bestFit(int partitionSizes[], int processSizes[])
{
    int allocation[PROCESSES];
    for (int i = 0; i < PROCESSES; i++)
    {
        allocation[i] = -1; // Initialize allocation as -1 (unallocated)
    }

    for (int i = 0; i < PROCESSES; i++)
    {
        int bestIndex = -1;
        for (int j = 0; j < PARTITIONS; j++)
        {
            if (partitionSizes[j] >= processSizes[i])
            {
                if (bestIndex == -1 || partitionSizes[j] < partitionSizes[bestIndex])
                {
                    bestIndex = j;
                }
            }
        }
        if (bestIndex != -1)
        {
            allocation[i] = bestIndex;
            partitionSizes[bestIndex] -= processSizes[i]; // Reduce partition size
        }
    }

    printf("Best Fit Allocation:\n");
    for (int i = 0; i < PROCESSES; i++)
    {
        if (allocation[i] != -1)
            printf("Process %d of size %d is allocated to partition %d\n", i + 1, processSizes[i], allocation[i] + 1);
        else
            printf("Process %d of size %d could not be allocated\n", i + 1, processSizes[i]);
    }
    printf("\n");
}

// Function to implement Worst Fit allocation
void worstFit(int partitionSizes[], int processSizes[])
{
    int allocation[PROCESSES];
    for (int i = 0; i < PROCESSES; i++)
    {
        allocation[i] = -1; // Initialize allocation as -1 (unallocated)
    }

    for (int i = 0; i < PROCESSES; i++)
    {
        int worstIndex = -1;
        for (int j = 0; j < PARTITIONS; j++)
        {
            if (partitionSizes[j] >= processSizes[i])
            {
                if (worstIndex == -1 || partitionSizes[j] > partitionSizes[worstIndex])
                {
                    worstIndex = j;
                }
            }
        }
        if (worstIndex != -1)
        {
            allocation[i] = worstIndex;
            partitionSizes[worstIndex] -= processSizes[i]; // Reduce partition size
        }
    }

    printf("Worst Fit Allocation:\n");
    for (int i = 0; i < PROCESSES; i++)
    {
        if (allocation[i] != -1)
            printf("Process %d of size %d is allocated to partition %d\n", i + 1, processSizes[i], allocation[i] + 1);
        else
            printf("Process %d of size %d could not be allocated\n", i + 1, processSizes[i]);
    }
    printf("\n");
}

int main()
{
    int partitionSizes[PARTITIONS], processSizes[PROCESSES];

    // Get input for memory partitions
    printf("Enter the sizes of %d memory partitions:\n", PARTITIONS);
    for (int i = 0; i < PARTITIONS; i++)
    {
        printf("Partition %d size: ", i + 1);
        scanf("%d", &partitionSizes[i]);
    }

    // Get input for processes
    printf("\nEnter the sizes of %d processes:\n", PROCESSES);
    for (int i = 0; i < PROCESSES; i++)
    {
        printf("Process %d size: ", i + 1);
        scanf("%d", &processSizes[i]);
    }

    // Make copies of partition sizes for each allocation strategy
    int partitionCopy1[PARTITIONS], partitionCopy2[PARTITIONS], partitionCopy3[PARTITIONS];

    // First Fit
    for (int i = 0; i < PARTITIONS; i++)
        partitionCopy1[i] = partitionSizes[i];
    firstFit(partitionCopy1, processSizes);

    // Best Fit
    for (int i = 0; i < PARTITIONS; i++)
        partitionCopy2[i] = partitionSizes[i];
    bestFit(partitionCopy2, processSizes);

    // Worst Fit
    for (int i = 0; i < PARTITIONS; i++)
        partitionCopy3[i] = partitionSizes[i];
    worstFit(partitionCopy3, processSizes);

    return 0;
}
