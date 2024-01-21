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
