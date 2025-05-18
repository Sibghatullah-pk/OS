#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <queue>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int BUFFER_SIZE = 5;
queue<int> buffer;
sem_t emptySlots, fullSlots;
pthread_mutex_t bufferMutex;
int bufferCount = 0; // shared variable to monitor buffer state

void logBufferState(const string& action, int id, int item) {
    cout << action << " " << id << ": " << item << " | Buffer size: " << bufferCount << endl << flush;
}

void* producer(void* arg) {
    int id = *((int*)arg);
    while (true) {
        int item = rand() % 100;
        sem_wait(&emptySlots);
        pthread_mutex_lock(&bufferMutex);

        buffer.push(item);
        bufferCount++;
        logBufferState("[Producer", id, item);

        pthread_mutex_unlock(&bufferMutex);
        sem_post(&fullSlots);

        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    int id = *((int*)arg);
    while (true) {
        sem_wait(&fullSlots);
        pthread_mutex_lock(&bufferMutex);

        if (!buffer.empty()) {
            int item = buffer.front();
            buffer.pop();
            bufferCount--;
            logBufferState("[Consumer", id, item);
        }

        pthread_mutex_unlock(&bufferMutex);
        sem_post(&emptySlots);

        sleep(2);
    }
    return NULL;
}

int main() {
    srand(time(0));

    sem_init(&emptySlots, 0, BUFFER_SIZE);
    sem_init(&fullSlots, 0, 0);
    pthread_mutex_init(&bufferMutex, NULL);

    const int NUM_PRODUCERS = 2;
    const int NUM_CONSUMERS = 2;

    pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];
    int pids[NUM_PRODUCERS], cids[NUM_CONSUMERS];

    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        pids[i] = i + 1;
        pthread_create(&producers[i], NULL, producer, &pids[i]);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        cids[i] = i + 1;
        pthread_create(&consumers[i], NULL, consumer, &cids[i]);
    }

    for (int i = 0; i < NUM_PRODUCERS; ++i) pthread_join(producers[i], NULL);
    for (int i = 0; i < NUM_CONSUMERS; ++i) pthread_join(consumers[i], NULL);

    return 0;
}
	

