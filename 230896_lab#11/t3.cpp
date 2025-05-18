#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <queue>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int NUM_PRINTERS = 3;
const int NUM_JOBS = 10;

queue<int> printQueue;
sem_t printers;      
pthread_mutex_t queueMutex;

void* addPrintJob(void* arg) {
    int jobId = *((int*)arg);

    pthread_mutex_lock(&queueMutex);
    printQueue.push(jobId);
    cout << "Added print job: " << jobId << endl << flush;
    pthread_mutex_unlock(&queueMutex);

    sem_wait(&printers);

    pthread_mutex_lock(&queueMutex);
    if (!printQueue.empty()) {
        int job = printQueue.front();
        printQueue.pop();
        cout << "Printing job: " << job << " on a printer." << endl << flush;
    }
    pthread_mutex_unlock(&queueMutex);

    sleep(2);

    cout << "Print job " << jobId << " finished." << endl << flush;
    sem_post(&printers);

    return NULL;
}

int main() {
    srand(time(0));

    sem_init(&printers, 0, NUM_PRINTERS);
    pthread_mutex_init(&queueMutex, NULL);

    pthread_t jobThreads[NUM_JOBS];
    int jobIds[NUM_JOBS];

    for (int i = 0; i < NUM_JOBS; ++i) {
        jobIds[i] = i + 1;
        if (pthread_create(&jobThreads[i], NULL, addPrintJob, &jobIds[i]) != 0) {
            cerr << "Failed to create thread for job " << i + 1 << endl;
        }
        sleep(1);
}
    for (int i = 0; i < NUM_JOBS; ++i) {
        pthread_join(jobThreads[i], NULL);
    }

    return 0;
}

	

