
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

sem_t resource;      
sem_t readCountMutex;
int readCount = 0;

void* reader(void* arg) {
    int id = *((int*)arg);

    while (true) {
        sem_wait(&readCountMutex);
        readCount++;
        if (readCount == 1) {
            sem_wait(&resource); 
        }
        sem_post(&readCountMutex);

        cout << "Reader " << id << " is reading." << endl << flush;
        sleep(1); 

        sem_wait(&readCountMutex);
        readCount--;
        if (readCount == 0) {
            sem_post(&resource); 
        }
        sem_post(&readCountMutex);

        sleep(rand() % 3 + 1); 
    }

    return NULL;
}

void* writer(void* arg) {
    int id = *((int*)arg);

    while (true) {
        sem_wait(&resource); 

        cout << "Writer " << id << " is writing." << endl << flush;
        sleep(2); 

        sem_post(&resource);

        sleep(rand() % 3 + 2);
    }

    return NULL;
}

int main() {
    srand(time(0));

    sem_init(&resource, 0, 1);
    sem_init(&readCountMutex, 0, 1);

    const int NUM_READERS = 3;
    const int NUM_WRITERS = 2;
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int rids[NUM_READERS], wids[NUM_WRITERS];

    for (int i = 0; i < NUM_READERS; ++i) {
        rids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &rids[i]);
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        wids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &wids[i]);
    }

    for (int i = 0; i < NUM_READERS; ++i) pthread_join(readers[i], NULL);
    for (int i = 0; i < NUM_WRITERS; ++i) pthread_join(writers[i], NULL);

    return 0;
}
	

