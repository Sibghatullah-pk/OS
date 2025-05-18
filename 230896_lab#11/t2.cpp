#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int NUM_PHILOSOPHERS = 5;
sem_t forks[NUM_PHILOSOPHERS];

void* philosopher(void* arg) {
    int id = *((int*)arg);

    while (true) {
        cout << "Philosopher " << id << " is thinking." << endl << flush;
        sleep(rand() % 3 + 1);

        int left = id;
        int right = (id + 1) % NUM_PHILOSOPHERS;

        if (id % 2 == 0) {
            sem_wait(&forks[left]);
            sem_wait(&forks[right]);
        } else {
            sem_wait(&forks[right]);
            sem_wait(&forks[left]);
        }

        cout << "Philosopher " << id << " is eating." << endl << flush;
        sleep(2);

        sem_post(&forks[left]);
        sem_post(&forks[right]);
    }

    return NULL;
}

int main() {
    srand(time(0));

   
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        sem_init(&forks[i], 0, 1);
    }

    pthread_t philThreads[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        ids[i] = i;
        if (pthread_create(&philThreads[i], NULL, philosopher, &ids[i]) != 0) {
            cerr << "Failed to create thread for philosopher " << i << endl;
        }
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_join(philThreads[i], NULL);
    }

    return 0;
}

	

