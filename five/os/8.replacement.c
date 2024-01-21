#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void fifo(int pages[], int numPages, int capacity);
void lru(int pages[], int numPages, int capacity);
void optimal(int pages[], int numPages, int capacity);

int main() 
{
    // Default input values for testing
    int numPages = 5;
    int pages[] = {1, 2, 3, 4, 1};
    int capacity = 3;

    printf("Number of pages: %d\n", numPages);
    printf("Page reference sequence: ");
    for (int i = 0; i < numPages; ++i) 
    {
        printf("%d ", pages[i]);
    }
    printf("\n");
    printf("Capacity of the page table: %d\n\n", capacity);

    printf("FIFO Page Replacement:\n");
    fifo(pages, numPages, capacity);

    printf("\nLRU Page Replacement:\n");
    lru(pages, numPages, capacity);

    printf("\nOptimal Page Replacement:\n");
    optimal(pages, numPages, capacity);

    return 0;
}

void fifo(int pages[], int numPages, int capacity) 
{
    int pageTable[capacity];
    int pageFaults = 0;

    // Initialize page table entries to -1 (indicating empty)
    for (int i = 0; i < capacity; ++i) 
    {
        pageTable[i] = -1;
    }

    int currentIndex = 0; // Index to track the oldest page in the page table

    for (int i = 0; i < numPages; ++i) 
    {
        int currentPage = pages[i];
        int found = 0;

        // Check if the page is already in the page table
        for (int j = 0; j < capacity; ++j) 
        {
            if (pageTable[j] == currentPage) 
            {
                found = 1;
                break;
            }
        }

        if (!found) 
        {
            // Page fault: Replace the oldest page in the page table
            pageTable[currentIndex] = currentPage;
            currentIndex = (currentIndex + 1) % capacity;
            pageFaults++;

            // Display the page table after each page reference
            printf("Page Table: ");
            for (int j = 0; j < capacity; ++j) 
            {
                printf("%d ", pageTable[j]);
            }
            printf("\n");
        }
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

void lru(int pages[], int numPages, int capacity) 
{
    int pageTable[capacity];
    int pageFaults = 0;

    // Initialize page table entries to -1 (indicating empty)
    for (int i = 0; i < capacity; ++i) 
    {
        pageTable[i] = -1;
    }

    for (int i = 0; i < numPages; ++i) 
    {
        int currentPage = pages[i];
        int found = 0;

        // Check if the page is already in the page table
        for (int j = 0; j < capacity; ++j) 
        {
            if (pageTable[j] == currentPage) 
            {
                found = 1;

                // Move the accessed page to the front (most recently used)
                int temp = pageTable[j];
                for (int k = j; k > 0; --k) 
                {
                    pageTable[k] = pageTable[k - 1];
                }
                pageTable[0] = temp;

                break;
            }
        }

        if (!found) 
        {
            // Page fault: Replace the least recently used page
            for (int j = capacity - 1; j > 0; --j) 
            {
                pageTable[j] = pageTable[j - 1];
            }
            pageTable[0] = currentPage;
            pageFaults++;

            // Display the page table after each page reference
            printf("Page Table: ");
            for (int j = 0; j < capacity; ++j) 
            {
                printf("%d ", pageTable[j]);
            }
            printf("\n");
        }
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

void optimal(int pages[], int numPages, int capacity) 
{
    int pageTable[capacity];
    int pageFaults = 0;

    // Initialize page table entries to -1 (indicating empty)
    for (int i = 0; i < capacity; ++i) 
    {
        pageTable[i] = -1;
    }

    for (int i = 0; i < numPages; ++i) 
    {
        int currentPage = pages[i];
        int found = 0;

        // Check if the page is already in the page table
        for (int j = 0; j < capacity; ++j) 
        {
            if (pageTable[j] == currentPage) 
            {
                found = 1;
                break;
            }
        }

        if (!found) 
        {
            // Page fault: Replace the page that will not be used for the longest time
            int replaceIndex = -1;
            for (int j = 0; j < capacity; ++j) 
            {
                int futureIndex = i + 1;
                while (futureIndex < numPages && pages[futureIndex] != pageTable[j]) 
                {
                    futureIndex++;
                }

                if (futureIndex == numPages) 
                {
                    replaceIndex = j;
                    break;
                }
            }

            if (replaceIndex != -1) 
            {
                pageTable[replaceIndex] = currentPage;
                pageFaults++;

                // Display the page table after each page reference
                printf("Page Table: ");
                for (int j = 0; j < capacity; ++j) 
                {
                    printf("%d ", pageTable[j]);
                }
                printf("\n");
            }
        }
    }

    printf("Total Page Faults: %d\n", pageFaults);
}