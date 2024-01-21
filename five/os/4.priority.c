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