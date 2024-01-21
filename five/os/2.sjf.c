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