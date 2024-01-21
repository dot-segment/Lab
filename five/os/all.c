Problem No: 01
Problem Name: Write a C program to simulate the CPU scheduling algorithm FCFS.
Code:
#include <stdio.
h>

// This structure represents a process
struct Process 
{
    // Process ID
    int id;

    // Arrival time of the process
    int arrival;

    // Burst time required for the process
    int burst;
};

// Function to perform FCFS scheduling
void fcfs(struct Process processes[], int n) 
{
    // Array to store completion time for each process
    int completionTime[n];

    // Array to store waiting time for each process
    int waitingTime[n];

    // Array to store turnaround time for each process
    int turnaroundTime[n];

    // Initialize completion time, waiting time, and turnaround time for the first process
    completionTime[0] = processes[0].burst;
    waitingTime[0] = 0;
    turnaroundTime[0] = processes[0].burst;

    // Calculate completion time, waiting time, and turnaround time for each subsequent process
    for (int i = 1; i < n; i++) 
    {
        completionTime[i] = completionTime[i - 1] + processes[i].burst;
        turnaroundTime[i] = completionTime[i] - processes[i].arrival;
        waitingTime[i] = turnaroundTime[i] - processes[i].burst;
    }

    // Display the results in a tabular format
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) 
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival,
               processes[i].burst, completionTime[i], waitingTime[i], turnaroundTime[i]);
    }
}

// Main function
int main() 
{
    // Three processes with their respective arrival and burst times
    struct Process processes[] = {
        {1, 0, 6}, 
        {2, 2, 8}, 
        {3, 5, 7}
    };

    // Calculate the number of processes
    int n = sizeof(processes) / sizeof(processes[0]);

    // Perform FCFS scheduling
    fcfs(processes, n);

    // Return 0 to indicate successful program execution
    return 0;
}














Problem No: 02
Problem Name: Write a C program to simulate the CPU scheduling algorithm SJF.
Code:
#include <stdio.h>

// Structure to represent a process
struct Process 
{
    // Process ID
    int id;

    // Burst time required for the process
    int burst;
};

// Function to perform Shortest Job First (SJF) scheduling
void sjf(struct Process processes[], int n) 
{
    // Array to store completion time for each process
    int completionTime[n];
    // Array to store waiting time for each process
    int waitingTime[n];
    // Array to store turnaround time for each process
    int turnaroundTime[n];

    // Sort processes based on burst time in ascending order (shortest job first)
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (processes[j].burst > processes[j + 1].burst) 
            {
                // Swap processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Calculate completion time, waiting time, and turnaround time for each process
    completionTime[0] = processes[0].burst;
    waitingTime[0] = 0;
    turnaroundTime[0] = processes[0].burst;

    for (int i = 1; i < n; i++) 
    {
        completionTime[i] = completionTime[i - 1] + processes[i].burst;
        // Assuming arrival time is 0 for all processes
        turnaroundTime[i] = completionTime[i] - 0;
        waitingTime[i] = turnaroundTime[i] - processes[i].burst;
    }

    // Display the results in tabular format
    printf("Process\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) 
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burst,
               completionTime[i], waitingTime[i], turnaroundTime[i]);
    }
}

// Main function
int main() {
    // Three processes with their respective burst times
    struct Process processes[] = {
        {1, 6}, 
        {2, 8}, 
        {3, 7}
    };
    int n = sizeof(processes) / sizeof(processes[0]);

    // Perform SJF scheduling
    sjf(processes, n);

    // Return 0 to indicate successful program execution
    return 0;
}



Problem No: 03
Problem Name: Write a C program to simulate the CPU scheduling algorithm Round Robin.
Code:
#include <stdio.h>

// Structure to represent a process
struct Process 
{
    // Process ID
    int id;

    // Burst time required for the process
    int burst;

    // Remaining burst time for the process
    int remaining;
};

// Function to perform Round Robin scheduling
void roundRobin(struct Process processes[], int n, int timeQuantum) 
{
    // Current time in the simulation
    int currentTime = 0;
    // Array to store completion time for each process
    int completionTime[n];
    // Array to store turnaround time for each process
    int turnaroundTime[n];
    // Array to store waiting time for each process
    int waitingTime[n];

    // Initialize remaining burst time for each process
    for (int i = 0; i < n; i++) 
    {
        processes[i].remaining = processes[i].burst;
    }

    // Simulate Round Robin scheduling
    while (1) 
    {
        // Flag to check if all processes are done
        int done = 1;

        // Iterate through each process
        for (int i = 0; i < n; i++) 
        {
            if (processes[i].remaining > 0) 
            {
                // At least one process is not done
                done = 0;

                // Check if process exceeds time quantum
                if (processes[i].remaining > timeQuantum) 
                {
                    // Process exceeds time quantum
                    currentTime += timeQuantum;
                    processes[i].remaining -= timeQuantum;
                }
                else 
                {
                    // Process finishes within time quantum
                    currentTime += processes[i].remaining;
                    completionTime[i] = currentTime;
                    turnaroundTime[i] = completionTime[i];
                    waitingTime[i] = turnaroundTime[i] - processes[i].burst;
                    processes[i].remaining = 0;
                }
            }
        }

        // Check if all processes are done
        if (done)
            break;  // All processes are done
    }

    // Display the results
    printf("Process\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) 
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burst,
               completionTime[i], waitingTime[i], turnaroundTime[i]);
    }
}

int main() 
{
    // Three processes with time quantum of 4
    struct Process processes[] = {
        {1, 24}, 
        {2, 10}, 
        {3, 15}
    };
    int n = sizeof(processes) / sizeof(processes[0]);
    int timeQuantum = 4;

    // Perform Round Robin scheduling
    roundRobin(processes, n, timeQuantum);

    return 0;
}
























Problem No: 04
Problem Name: Write a C program to simulate the CPU scheduling algorithm Priority scheduling.
Code:
#include <stdio.h>
// Structure to represent a process
struct Process 
{
    // Process ID
    int id;
    // Burst time required for the process
    int burst;
    // Priority of the process
    int priority;
};

// Function to perform Priority scheduling
void priorityScheduling(struct Process processes[], int n) 
{
    // Array to store completion time for each process
    int completionTime[n];
    // Array to store turnaround time for each process
    int turnaroundTime[n];
    // Array to store waiting time for each process
    int waitingTime[n];

    // Sort processes based on priority (lower value indicates higher priority)
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (processes[j].priority > processes[j + 1].priority) 
            {
                // Swap processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Calculate completion time, waiting time, and turnaround time for each process
    completionTime[0] = processes[0].burst;
    waitingTime[0] = 0;
    turnaroundTime[0] = processes[0].burst;

    for (int i = 1; i < n; i++) 
    {
        completionTime[i] = completionTime[i - 1] + processes[i].burst;
        turnaroundTime[i] = completionTime[i];
        waitingTime[i] = turnaroundTime[i] - processes[i].burst;
    }

    // Display the results in tabular format
    printf("Process\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) 
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burst,
               processes[i].priority, completionTime[i], waitingTime[i], turnaroundTime[i]);
    }
}

// Main function
int main() 
{
    // Three processes with their respective burst times and priorities
    struct Process processes[] = {
        {1, 6, 2}, 
        {2, 8, 1}, 
        {3, 7, 3}
    };
    int n = sizeof(processes) / sizeof(processes[0]);

    // Perform Priority scheduling
    priorityScheduling(processes, n);

    // Return 0 to indicate successful program execution
    return 0;
}



Problem No: 05
Problem Name: Write a C program to simulate the producer consumer problem using semaphore.
Code:
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

// Shared buffer
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Semaphores
sem_t mutex, empty, full;

// Producer function
void *producer(void *arg) 
{
    int item;

    for (int i = 0; i < 10; i++) 
    {
        // Generate a random item
        item = rand();
        
        // Wait for an empty slot in the buffer
        sem_wait(&empty);
        // Enter critical section
        sem_wait(&mutex);  

        // Produce item and add to the buffer
        printf("Produced: %d\n", item);
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;

        // Exit critical section
        sem_post(&mutex);
        // Signal that the buffer is no longer empty
        sem_post(&full);   
    }

    pthread_exit(NULL);
}

// Consumer function
void *consumer(void *arg) 
{
    int item;

    for (int i = 0; i < 10; i++) 
    {
        // Wait for a full slot in the buffer
        sem_wait(&full);
        // Enter critical section
        sem_wait(&mutex);  

        // Consume item from the buffer
        item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        // Exit critical section
        sem_post(&mutex);
        // Signal that the buffer is no longer full
        sem_post(&empty);  
    }

    pthread_exit(NULL);
}

int main() 
{
    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    // Create producer and consumer threads
    pthread_t producerThread, consumerThread;
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    // Join threads
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}















Problem No: 06
Problem Name: Write a C program to simulate the concept of dining philosophers problem.
Code:
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 2

pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];
sem_t room;

void *philosopher(void *arg) 
{
    int id = *((int *)arg);
    int left_chopstick = id;
    int right_chopstick = (id + 1) % NUM_PHILOSOPHERS;

    int cycles = 0;
    // Change this condition as needed
    while (cycles < 5) {  
        // Enter the room
        sem_wait(&room);

        // Pick up left chopstick
        pthread_mutex_lock(&chopsticks[left_chopstick]);
        printf("Philosopher %d picked up left chopstick %d\n", id, left_chopstick);

        // Pick up right chopstick
        pthread_mutex_lock(&chopsticks[right_chopstick]);
        printf("Philosopher %d picked up right chopstick %d\n", id, right_chopstick);

        // Release room
        sem_post(&room);

        // Eat
        printf("Philosopher %d is eating\n", id);
        // Simulating eating time
        sleep(2);  

        // Release right chopstick
        pthread_mutex_unlock(&chopsticks[right_chopstick]);
        printf("Philosopher %d released right chopstick %d\n", id, right_chopstick);

        // Release left chopstick
        pthread_mutex_unlock(&chopsticks[left_chopstick]);
        printf("Philosopher %d released left chopstick %d\n", id, left_chopstick);

        // Think
        printf("Philosopher %d is thinking\n", id);
        sleep(1);  // Simulating thinking time

        // Increase the counter after completing a cycle
        cycles++;
    }

    pthread_exit(NULL);
}

int main() 
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // The room allows NUM_PHILOSOPHERS - 1 philosophers to enter
    sem_init(&room, 0, NUM_PHILOSOPHERS - 1);  

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) 
    {
        pthread_mutex_init(&chopsticks[i], NULL);
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) 
    {
        pthread_join(philosophers[i], NULL);
        pthread_mutex_destroy(&chopsticks[i]);
    }

    sem_destroy(&room);

    return 0;
}
























Problem No:07
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























Problem No: 08
Problem Name: Write a C program to implement page replacement techniques - 
FIFO 
LRU 
Optimal.

Code:
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






Problem No: 09
Problem Name: Write a C program to simulate all files allocation strategies -  
Sequential
Indexed
Linked
Code:
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




















Problem No: 10
Problem Name: Write a C program for banker’s algorithm using deadlock method.
Code:
#include <stdio.h>

int main() 
{
    int n, m;

    // Prompt the user to enter the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Prompt the user to enter the number of resources
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], avail[m], f[n], ans[n];

    // Input allocation matrix
    printf("Enter the Allocation Matrix:\n");
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input max matrix
    printf("Enter the Max Matrix:\n");
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            scanf("%d", &max[i][j]);
        }
    }

    // Input available resources
    printf("Enter the Available Resources:\n");
    for (int i = 0; i < m; i++) 
    {
        scanf("%d", &avail[i]);
    }

    // Declare index variable for index tracking
    int index = 0;
    for (int k = 0; k < n; k++) 
    {
        f[k] = 0;
    }

    // need array declare for stored need resouces
    int need[n][m];
    for (int i = 0; i < n; i++) 
    {
        //calculating need resources each process
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }

    // Display Allocation matrix
    int a, b;
    printf("\n Allocation matrix: \n");
    for (a = 0; a < n; a++) 
    {
        for (b = 0; b < n; b++) 
        {
            printf("%d ", alloc[a][b]);
        }
        printf("\n");
    }

    // Display maximum resouces matrix
    printf("\n Max matrix: \n");
    for (a = 0; a < n; a++) 
    {
        for (b = 0; b < n; b++) 
        {
            printf("%d ", max[a][b]);
        }
        printf("\n");
    }

    // Display Need resources matrix
    printf("\n Need matrix: \n");
    for (a = 0; a < n; a++) 
    {
        for (b = 0; b < n; b++) 
        {
            printf("%d ", need[a][b]);
        }
        printf("\n");
    }
    
    /* Y is used to iterate through the resources for a particular process */
    int y = 0;
    // Loop through each process
    for (int k = 0; k < n; k++) 
    {
        // Loop through each process to find a safe sequence
        for (int i = 0; i < n; i++) 
        {
            // Check if the process is not yet finished (f[i] == 0)
            if (f[i] == 0) 
            {
                int flag = 0;
                // Check if the resources needed for the process can be satisfied
                for (int j = 0; j < m; j++) 
                {
                    if (need[i][j] > avail[j]) 
                    {
                        // If the resources are not sufficient, set flag to 1 and break
                        flag = 1;
                        break;
                    }
                }
                // If the process can be executed safely
                if (flag == 0) 
                {
                    // Add the process to the safe sequence
                    ans[index++] = i;
                    // Update the available resources after executing the process
                    for (y = 0; y < m; y++)
                        avail[y] += alloc[i][y];
                    // Mark the process as finished
                    f[i] = 1;
                }
            }
        }
    }

    int flag = 1;
    // To check if the sequence is safe or not
    for (int i = 0; i < n; i++) 
    {
        if (f[i] == 0) 
        {
            flag = 0;
            // Print a message if the sequence is not safe
            printf("The given sequence is not safe");
            break;
        }
    }

    if (flag == 1) 
    {
        // Print the safe sequence if the sequence is safe
        printf("Following is the SAFE Sequence\n");
        for (int i = 0; i < n - 1; i++)
            printf(" P%d ->", ans[i]);
        printf(" P%d\n", ans[n - 1]);
    }

    return 0;
}
