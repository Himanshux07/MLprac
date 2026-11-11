
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

// Mutex for protecting shared fork resources
pthread_mutex_t fork_mutex[N];

// Function executed by each philosopher
void* philosopher(void* arg)
{
    int id = *(int*)arg;

    int left = id;
    int right = (id + 1) % N;

    while (1)
    {
        // Philosopher is thinking
        printf("Philosopher %d is THINKING\n", id + 1);
        sleep(1);

        // Odd-Even solution to avoid deadlock

        if (id % 2 == 0)
        {
            // Even philosopher picks left fork first
            pthread_mutex_lock(&fork_mutex[left]);
            printf("Philosopher %d picked LEFT fork %d\n",
                   id + 1, left + 1);

            // Then picks right fork
            pthread_mutex_lock(&fork_mutex[right]);
            printf("Philosopher %d picked RIGHT fork %d\n",
                   id + 1, right + 1);
        }
        else
        {
            // Odd philosopher picks right fork first
            pthread_mutex_lock(&fork_mutex[right]);
            printf("Philosopher %d picked RIGHT fork %d\n",
                   id + 1, right + 1);

            // Then picks left fork
            pthread_mutex_lock(&fork_mutex[left]);
            printf("Philosopher %d picked LEFT fork %d\n",
                   id + 1, left + 1);
        }

        // Both forks are acquired, so philosopher can eat
        printf("Philosopher %d is EATING\n", id + 1);
        sleep(2);

        // Release both forks after eating
        pthread_mutex_unlock(&fork_mutex[left]);
        pthread_mutex_unlock(&fork_mutex[right]);

        printf("Philosopher %d finished EATING\n", id + 1);
    }

    return NULL;
}

int main()
{
    pthread_t threads[N];
    int id[N];

    // Initialize mutex for all five forks
    for (int i = 0; i < N; i++)
    {
        pthread_mutex_init(&fork_mutex[i], NULL);
    }

    // Create five philosopher threads
    for (int i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &id[i]);
    }

    // Wait for all philosopher threads
    for (int i = 0; i < N; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Destroy all mutex locks
    for (int i = 0; i < N; i++)
    {
        pthread_mutex_destroy(&fork_mutex[i]);
    }

    return 0;
}
