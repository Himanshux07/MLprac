
#include <stdio.h>

int main()
{
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    // Arrays based on n and m
    int allocation[n][m];
    int maxNeed[n][m];
    int need[n][m];

    int available[m];
    int work[m];
    int finish[n];
    int safeSequence[n];

    // Initialize finish array
    for(int i = 0; i < n; i++)
    {
        finish[i] = 0;
    }

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input Maximum Matrix
    printf("\nEnter Maximum Matrix:\n");

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            scanf("%d", &maxNeed[i][j]);
        }
    }

    // Calculate Need Matrix
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            need[i][j] = maxNeed[i][j] - allocation[i][j];

            if(need[i][j] < 0)
            {
                printf("Invalid input!");
                return 0;
            }
        }
    }

    // Input Available Resources
    printf("\nEnter Available Resources:\n");

    for(int j = 0; j < m; j++)
    {
        scanf("%d", &available[j]);
        work[j] = available[j];
    }

    int count = 0;

    // Find Safe Sequence
    while(count < n)
    {
        int found = 0;

        for(int i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                int possible = 1;

                for(int j = 0; j < m; j++)
                {
                    if(need[i][j] > work[j])
                    {
                        possible = 0;
                        break;
                    }
                }

                if(possible)
                {
                    // Release allocated resources
                    for(int j = 0; j < m; j++)
                    {
                        work[j] += allocation[i][j];
                    }

                    safeSequence[count] = i;
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }

        if(found == 0)
        {
            break;
        }
    }

    // Display Need Matrix
    printf("\nNeed Matrix:\n");

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            printf("%d ", need[i][j]);
        }

        printf("\n");
    }

    // Check Safe State
    if(count == n)
    {
        printf("\nSystem is in SAFE state.\n");

        printf("Safe Sequence: ");

        for(int i = 0; i < n; i++)
        {
            printf("P%d", safeSequence[i]);

            if(i != n - 1)
                printf(" -> ");
        }

        printf("\n");
    }
    else
    {
        printf("\nSystem is NOT in a safe state.\n");
    }

    return 0;
}
