#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define NUM_CYCLES 3

sem_t forks[NUM_PHILOSOPHERS];
sem_t mutex;

void *philospher(void *num)
{
    int id = *(int *)num;

    for (int i = 0; i < NUM_CYCLES; i++)
    {
        printf("Philospher %d is thinking ...\n", id);
        sleep(1);

        sem_wait(&mutex);
        sem_wait(&forks[id]);
        sem_wait(&forks[(id + 1) % NUM_PHILOSOPHERS]);

        sem_post(&mutex);

        printf("Philosopher %d is eating ...\n", id);
        sleep(2);

        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % NUM_PHILOSOPHERS]);
    }

    printf("Philosopher %d has finished their %d cycles.\n", id, NUM_CYCLES);
    return NULL;
}

int main()
{
    pthread_t philosphers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    sem_init(&mutex, 0, 1);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_init(&forks[i], 0, 1);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        philosopher_ids[i] = i;
        pthread_create(&philosphers[i], NULL, philospher, &philosopher_ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(philosphers[i], NULL);
    }

    printf("All philosophers have finished their %d cycles.", NUM_CYCLES);

    return 0;
}