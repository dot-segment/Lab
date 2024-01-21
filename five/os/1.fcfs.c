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