Problem Name:  Write a C program to simulate the following contiguous memory allocation-  
 Worst Fit 
Best Fit 
First Fit.

Code:
#include <stdio.h>
#include <stdlib.h>

// Structure to represent a block of memory
struct Block 
{
    int size;
    int allocated;
};

// Function prototypes
void allocateFirstFit(struct Block *memory, int numBlocks, int processSize);
void allocateBestFit(struct Block *memory, int numBlocks, int processSize);
void allocateWorstFit(struct Block *memory, int numBlocks, int processSize);
void displayMemory(struct Block *memory, int numBlocks);

int main() 
{
    // Number of memory blocks
    int numBlocks = 5;

    // Memory blocks with hard-coded sizes
    struct Block memory[] = {
        {100, 0}, 
        {200, 0}, 
        {50, 0}, 
        {300, 0}, 
        {150, 0}
    };

    // Allocate processes using different strategies
    int processSize = 120;

    printf("First Fit:\n");
    allocateFirstFit(memory, numBlocks, processSize);
    displayMemory(memory, numBlocks);

    printf("\nBest Fit:\n");
    allocateBestFit(memory, numBlocks, processSize);
    displayMemory(memory, numBlocks);

    printf("\nWorst Fit:\n");
    allocateWorstFit(memory, numBlocks, processSize);
    displayMemory(memory, numBlocks);

    return 0;
}

// Function to allocate memory using First Fit strategy
void allocateFirstFit(struct Block *memory, int numBlocks, int processSize) 
{
    for (int i = 0; i < numBlocks; ++i) 
    {
        if (!memory[i].allocated && memory[i].size >= processSize) 
        {
            memory[i].allocated = 1;
            printf("Process allocated to block %d\n", i + 1);
            break;
        }
    }
}

// Function to allocate memory using Best Fit strategy
void allocateBestFit(struct Block *memory, int numBlocks, int processSize) 
{
    int bestFitIndex = -1;
    for (int i = 0; i < numBlocks; ++i) 
    {
        if (!memory[i].allocated && memory[i].size >= processSize) 
        {
            if (bestFitIndex == -1 || memory[i].size < memory[bestFitIndex].size) 
            {
                bestFitIndex = i;
            }
        }
    }

    if (bestFitIndex != -1) 
    {
        memory[bestFitIndex].allocated = 1;
        printf("Process allocated to block %d\n", bestFitIndex + 1);
    } 
    else 
    {
        printf("No suitable block found for allocation.\n");
    }
}

// Function to allocate memory using Worst Fit strategy
void allocateWorstFit(struct Block *memory, int numBlocks, int processSize) 
{
    int worstFitIndex = -1;
    for (int i = 0; i < numBlocks; ++i) 
    {
        if (!memory[i].allocated && memory[i].size >= processSize) 
        {
            if (worstFitIndex == -1 || memory[i].size > memory[worstFitIndex].size) 
            {
                worstFitIndex = i;
            }
        }
    }

    if (worstFitIndex != -1) 
    {
        memory[worstFitIndex].allocated = 1;
        printf("Process allocated to block %d\n", worstFitIndex + 1);
    } else 
    {
        printf("No suitable block found for allocation.\n");
    }
}

// Function to display the memory status
void displayMemory(struct Block *memory, int numBlocks) 
{
    printf("Memory Blocks:\n");
    for (int i = 0; i < numBlocks; ++i) 
    {
        printf("Block %d: Size = %d, Allocated = %s\n", i + 1, memory[i].size,
               memory[i].allocated ? "Yes" : "No");
    }
}