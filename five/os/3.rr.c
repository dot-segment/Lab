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