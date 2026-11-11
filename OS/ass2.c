
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Bubble Sort function
void bubbleSort(int arr[], int n)
{
    int i, j, temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Display array
void display(int arr[], int n)
{
    int i;

    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

// Function to demonstrate Zombie Process
void demonstrateZombie()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        printf("\nZombie Child PID: %d\n", getpid());
        printf("Zombie child is terminating...\n");
        exit(0);
    }
    else if (pid > 0)
    {
        printf("Zombie Parent PID: %d\n", getpid());

        // Delay wait() to demonstrate zombie
        sleep(5);

        printf("Child may be in Zombie state.\n");
        printf("Check using: ps -el | grep ' Z '\n");

        wait(NULL);

        printf("Parent collected child status.\n");
        printf("Zombie process removed.\n");
    }
    else
    {
        perror("Fork failed");
    }
}

// Function to demonstrate Orphan Process
void demonstrateOrphan()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        printf("\nOrphan Child Started\n");
        printf("Child PID: %d\n", getpid());
        printf("Initial Parent PID: %d\n", getppid());

        sleep(5);

        printf("\nAfter Parent Termination:\n");
        printf("Child PID: %d\n", getpid());
        printf("New Parent PID: %d\n", getppid());

        printf("Orphan child completed.\n");
        exit(0);
    }
    else if (pid > 0)
    {
        printf("Orphan Parent PID: %d\n", getpid());
        printf("Parent is terminating...\n");

        exit(0);
    }
    else
    {
        perror("Fork failed");
    }
}

int main()
{
    int n, arr[100], i;
    pid_t pid;

    // Accept integers
    printf("Enter number of integers: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100)
    {
        printf("Invalid input!\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);

    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // Create child process
    pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        // Child process
        printf("\n--- CHILD PROCESS ---\n");
        printf("Child PID: %d\n", getpid());

        bubbleSort(arr, n);

        printf("Child sorted array: ");
        display(arr, n);

        exit(0);
    }
    else
    {
        // Parent process
        printf("\n--- PARENT PROCESS ---\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        bubbleSort(arr, n);

        printf("Parent sorted array: ");
        display(arr, n);

        // Wait for child
        wait(NULL);

        printf("\nParent: Child process completed.\n");

        // Demonstrate Zombie
        printf("\n========== ZOMBIE DEMONSTRATION ==========\n");
        demonstrateZombie();

        // Demonstrate Orphan
        printf("\n========== ORPHAN DEMONSTRATION ==========\n");
        demonstrateOrphan();
    }

    return 0;
}
