
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;

// Counting semaphores
sem_t empty, full;

// Mutex for mutual exclusion
pthread_mutex_t mutex;

// Producer function
void* producer(void* arg)
{
    int item;

    for (int i = 1; i <= 10; i++)
    {
        item = i;

        sem_wait(&empty);  // Wait for empty slot
        pthread_mutex_lock(&mutex);

        buffer[in] = item;

        printf("Producer produced: %d\n", item);

        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);   // Increase full slots

        sleep(1);
    }

    return NULL;
}

// Consumer function
void* consumer(void* arg)
{
    int item;

    for (int i = 1; i <= 10; i++)
    {
        sem_wait(&full);   // Wait for available item
        pthread_mutex_lock(&mutex);

        item = buffer[out];

        printf("Consumer consumed: %d\n", item);

        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);  // Increase empty slots

        sleep(2);
    }

    return NULL;
}

int main()
{
    pthread_t p, c;

    // Initialize semaphores
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    // Wait for both threads
    pthread_join(p, NULL);
    pthread_join(c, NULL);

    // Destroy synchronization variables
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
