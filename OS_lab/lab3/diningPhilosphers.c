#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5 // Number of philosophers

sem_t forks[N];            // Semaphore array representing forks
pthread_t philosophers[N]; // Philosopher threads
int philosopher_id[N];     // Philosopher IDs

// Function to simulate philosopher's thinking
void think(int philosopher_num)
{
    printf("Philosopher %d is thinking.\n", philosopher_num);
    sleep(1);
}

// Function to simulate philosopher picking up forks
void pick_up_forks(int philosopher_num)
{
    int left_fork = philosopher_num;            // Left fork is the philosopher's own number
    int right_fork = (philosopher_num + 1) % N; // Right fork is the next fork in the circle

    // Wait on both forks (ensuring the philosopher picks up both forks)
    if (philosopher_num % 2 == 0)
    { // Avoid deadlock by alternating the order of picking up forks
        sem_wait(&forks[left_fork]);
        sem_wait(&forks[right_fork]);
    }
    else
    {
        sem_wait(&forks[right_fork]);
        sem_wait(&forks[left_fork]);
    }
    printf("Philosopher %d picked up forks %d and %d.\n", philosopher_num, left_fork, right_fork);
}

// Function to simulate philosopher eating
void eat(int philosopher_num)
{
    printf("Philosopher %d is eating.\n", philosopher_num);
    sleep(2);
}

// Function to simulate philosopher putting down forks
void put_down_forks(int philosopher_num)
{
    int left_fork = philosopher_num;            // Left fork is the philosopher's own number
    int right_fork = (philosopher_num + 1) % N; // Right fork is the next fork in the circle

    // Release the forks
    sem_post(&forks[left_fork]);
    sem_post(&forks[right_fork]);

    printf("Philosopher %d put down forks %d and %d.\n", philosopher_num, left_fork, right_fork);
}

// Philosopher's routine
void *philosopher_routine(void *num)
{
    int philosopher_num = *(int *)num;

    while (1)
    {
        think(philosopher_num);
        pick_up_forks(philosopher_num);
        eat(philosopher_num);
        put_down_forks(philosopher_num);
    }
}

int main()
{
    // Initialize the semaphores (each fork is available initially)
    for (int i = 0; i < N; i++)
    {
        sem_init(&forks[i], 0, 1);
        philosopher_id[i] = i; // Set philosopher IDs
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++)
    {
        pthread_create(&philosophers[i], NULL, philosopher_routine, &philosopher_id[i]);
    }

    // Join the philosopher threads (this program will run infinitely)
    for (int i = 0; i < N; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores (though this point won't be reached due to infinite loop)
    for (int i = 0; i < N; i++)
    {
        sem_destroy(&forks[i]);
    }

    return 0;
}
