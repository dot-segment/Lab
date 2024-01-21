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
