#include <stdio.h>
#include <stdlib.h>

#define STORAGE_SIZE 1000

// Define a structure to represent a file
typedef struct 
{
    // Unique identifier for the file
    int file_id;
    // Size of the file
    int size;
    // Starting position in the storage array
    int start;
    // Flag indicating whether the file is allocated or not
    int allocated;
} File;

// Function to initialize the storage array
void initializeStorage(int storage[], int size);

// Function for sequential file allocation
void sequentialAllocation(int storage[], File files[], int numFiles);

// Function to print file allocation information
void printFileAllocation(File files[], int numFiles);

int main() 
{
    int storage[STORAGE_SIZE];
    // Array of File structures representing files to be allocated
    File files[] = {
        {1, 100, 0, 0},
        {2, 200, 0, 0},
        {3, 50, 0, 0},
        {4, 300, 0, 0}
    };

    initializeStorage(storage, STORAGE_SIZE);

    printf("Sequential File Allocation:\n");
    sequentialAllocation(storage, files, sizeof(files) / sizeof(files[0]));
    printFileAllocation(files, sizeof(files) / sizeof(files[0]));

    return 0;
}

// Function to initialize the storage array to zeros
void initializeStorage(int storage[], int size) 
{
    for (int i = 0; i < size; ++i) 
    {
        storage[i] = 0;
    }
}

// Function to perform sequential file allocation
void sequentialAllocation(int storage[], File files[], int numFiles) 
{
    int current_position = 0;

    for (int i = 0; i < numFiles; ++i) 
    {
        if (current_position + files[i].size <= STORAGE_SIZE) 
        {
            files[i].start = current_position;
            files[i].allocated = 1;

            // Allocate the file in the storage by setting the corresponding positions to the file_id
            for (int j = current_position; j < current_position + files[i].size; ++j) 
            {
                storage[j] = files[i].file_id;
            }

            current_position += files[i].size;
        } 
        else 
        {
            printf("Not enough space for file %d\n", files[i].file_id);
        }
    }
}

// Function to print file allocation information
void printFileAllocation(File files[], int numFiles) 
{
    printf("\nFile Allocation:\n");

    for (int i = 0; i < numFiles; ++i) 
    {
        printf("File %d: Start Position: %d, Size: %d, Allocated: %s\n",
               files[i].file_id, files[i].start, files[i].size,
               (files[i].allocated ? "Yes" : "No"));
    }
}
