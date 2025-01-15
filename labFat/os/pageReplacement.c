#include <stdio.h>
#include <limits.h>

#define MAX_PAGES 50
#define FRAME_SIZE 4

// Function to check if a page is present in frames
int isPagePresent(int frames[], int page)
{
    for (int i = 0; i < FRAME_SIZE; i++)
    {
        if (frames[i] == page)
        {
            return 1; // Page found
        }
    }
    return 0; // Page not found
}

// FIFO Page Replacement Algorithm
int fifo(int pages[], int n)
{
    int frames[FRAME_SIZE] = {-1, -1, -1, -1};
    int index = 0, pageFaults = 0;

    for (int i = 0; i < n; i++)
    {
        if (!isPagePresent(frames, pages[i]))
        {
            frames[index] = pages[i];
            index = (index + 1) % FRAME_SIZE;
            pageFaults++;
        }
    }
    return pageFaults;
}

// Optimal Page Replacement Algorithm
int optimal(int pages[], int n)
{
    int frames[FRAME_SIZE] = {-1, -1, -1, -1};
    int pageFaults = 0;

    for (int i = 0; i < n; i++)
    {
        if (!isPagePresent(frames, pages[i]))
        {
            int farthest = -1, replaceIndex = -1;
            for (int j = 0; j < FRAME_SIZE; j++)
            {
                int k;
                for (k = i + 1; k < n; k++)
                {
                    if (frames[j] == pages[k])
                    {
                        if (k > farthest)
                        {
                            farthest = k;
                            replaceIndex = j;
                        }
                        break;
                    }
                }
                if (k == n)
                { // Page not found in future reference
                    replaceIndex = j;
                    break;
                }
            }
            // frames[replaceIndex == -1 ? 0 : replaceIndex] = pages[i];
            frames[replaceIndex] = pages[i];
            pageFaults++;
        }
    }
    return pageFaults;
}

// LRU Page Replacement Algorithm
int lru(int pages[], int n)
{
    int frames[FRAME_SIZE] = {-1, -1, -1, -1}; // Initialize frames
    int lastUsed[FRAME_SIZE] = {0, 0, 0, 0};   // To track usage of each frame
    int pageFaults = 0;
    int time = 0; // A global counter to track the order of usage

    for (int i = 0; i < n; i++)
    {
        int found = isPagePresent(frames, pages[i]);
        int replaceIndex = -1;

        if (!found)
        {
            // If the page is not found, we need to replace one page
            int leastRecent = INT_MAX;

            // Find the least recently used page by checking lastUsed[]
            for (int j = 0; j < FRAME_SIZE; j++)
            {
                if (frames[j] == -1)
                { // Empty frame case, fill it
                    replaceIndex = j;
                    break;
                }
                if (lastUsed[j] < leastRecent)
                {
                    leastRecent = lastUsed[j];
                    replaceIndex = j;
                }
            }

            // Replace the least recently used page
            frames[replaceIndex] = pages[i];
            pageFaults++;
        }

        // Update the last used time for the current page
        // Increment the global "time" counter and use it to track usage
        for (int j = 0; j < FRAME_SIZE; j++)
        {
            if (frames[j] == pages[i])
            {
                lastUsed[j] = time; // Update time for the page that's been accessed
                break;
            }
        }
        time++; // Increment the global time counter
    }

    return pageFaults;
}

int main()
{
    int n, pageFaultsFIFO, pageFaultsOptimal, pageFaultsLRU;
    int pages[MAX_PAGES];

    // Input reference string from the user
    printf("Enter the number of pages (minimum 15): ");
    scanf("%d", &n);
    if (n < 15)
    {
        printf("Minimum allowed pages are 15.\n");
        return 1;
    }

    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    // Call page replacement algorithms
    pageFaultsFIFO = fifo(pages, n);
    pageFaultsOptimal = optimal(pages, n);
    pageFaultsLRU = lru(pages, n);

    // Calculate hits and miss ratios
    int hitsFIFO = n - pageFaultsFIFO;
    int hitsOptimal = n - pageFaultsOptimal;
    int hitsLRU = n - pageFaultsLRU;

    printf("\nFIFO: \nPage Faults = %d, Hits = %d, Hit Ratio = %.2f, Miss Ratio = %.2f\n",
           pageFaultsFIFO, hitsFIFO, (float)hitsFIFO / n, (float)pageFaultsFIFO / n);
    printf("Optimal: \nPage Faults = %d, Hits = %d, Hit Ratio = %.2f, Miss Ratio = %.2f\n",
           pageFaultsOptimal, hitsOptimal, (float)hitsOptimal / n, (float)pageFaultsOptimal / n);
    printf("LRU: \nPage Faults = %d, Hits = %d, Hit Ratio = %.2f, Miss Ratio = %.2f\n",
           pageFaultsLRU, hitsLRU, (float)hitsLRU / n, (float)pageFaultsLRU / n);

    return 0;
}
