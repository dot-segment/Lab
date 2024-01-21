#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 2

pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];
sem_t room;

void *philosopher(void *arg) 
{
    int id = *((int *)arg);
    int left_chopstick = id;
    int right_chopstick = (id + 1) % NUM_PHILOSOPHERS;

    int cycles = 0;
    // Change this condition as needed
    while (cycles < 5) {  
        // Enter the room
        sem_wait(&room);

        // Pick up left chopstick
        pthread_mutex_lock(&chopsticks[left_chopstick]);
        printf("Philosopher %d picked up left chopstick %d\n", id, left_chopstick);

        // Pick up right chopstick
        pthread_mutex_lock(&chopsticks[right_chopstick]);
        printf("Philosopher %d picked up right chopstick %d\n", id, right_chopstick);

        // Release room
        sem_post(&room);

        // Eat
        printf("Philosopher %d is eating\n", id);
        // Simulating eating time
        sleep(2);  

        // Release right chopstick
        pthread_mutex_unlock(&chopsticks[right_chopstick]);
        printf("Philosopher %d released right chopstick %d\n", id, right_chopstick);

        // Release left chopstick
        pthread_mutex_unlock(&chopsticks[left_chopstick]);
        printf("Philosopher %d released left chopstick %d\n", id, left_chopstick);

        // Think
        printf("Philosopher %d is thinking\n", id);
        sleep(1);  // Simulating thinking time

        // Increase the counter after completing a cycle
        cycles++;
    }

    pthread_exit(NULL);
}

int main() 
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // The room allows NUM_PHILOSOPHERS - 1 philosophers to enter
    sem_init(&room, 0, NUM_PHILOSOPHERS - 1);  

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) 
    {
        pthread_mutex_init(&chopsticks[i], NULL);
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) 
    {
        pthread_join(philosophers[i], NULL);
        pthread_mutex_destroy(&chopsticks[i]);
    }

    sem_destroy(&room);

    return 0;
}
