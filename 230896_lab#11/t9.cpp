#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <queue>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

sem_t highPrioritySem;
sem_t lowPrioritySem;
pthread_mutex_t queueMutex;

queue<int> highPriorityQueue;
queue<int> lowPriorityQueue;

void* scheduler(void* arg) {
    while (true) {
        if (sem_trywait(&highPrioritySem) == 0) {
            pthread_mutex_lock(&queueMutex);
            if (!highPriorityQueue.empty()) {
                int task = highPriorityQueue.front();
                highPriorityQueue.pop();
                cout << "[Scheduler] Executing high priority task: " << task << endl << flush;
            }
            pthread_mutex_unlock(&queueMutex);
        } else if (sem_trywait(&lowPrioritySem) == 0) {
            pthread_mutex_lock(&queueMutex);
            if (!lowPriorityQueue.empty()) {
                int task = lowPriorityQueue.front();
                lowPriorityQueue.pop();
                cout << "[Scheduler] Executing low priority task: " << task << endl << flush;
            }
            pthread_mutex_unlock(&queueMutex);
        }
        sleep(1);
    }
    return NULL;
}

void* submitTask(void* arg) {
    int id = *((int*)arg);
    int priority = rand() % 2; // 0 = low, 1 = high

    pthread_mutex_lock(&queueMutex);
    if (priority == 1) {
        highPriorityQueue.push(id);
        sem_post(&highPrioritySem);
        cout << "Task " << id << " submitted with HIGH priority." << endl << flush;
    } else {
        lowPriorityQueue.push(id);
        sem_post(&lowPrioritySem);
        cout << "Task " << id << " submitted with LOW priority." << endl << flush;
    }
    pthread_mutex_unlock(&queueMutex);

    return NULL;
}

int main() {
    srand(time(0));

    sem_init(&highPrioritySem, 0, 0);
    sem_init(&lowPrioritySem, 0, 0);
    pthread_mutex_init(&queueMutex, NULL);

    const int NUM_TASKS = 10;
    pthread_t tasks[NUM_TASKS];
    int ids[NUM_TASKS];

    pthread_t sched;
    pthread_create(&sched, NULL, scheduler, NULL);

    for (int i = 0; i < NUM_TASKS; ++i) {
        ids[i] = i + 1;
        pthread_create(&tasks[i], NULL, submitTask, &ids[i]);
        sleep(1); // stagger task submissions
    }

    for (int i = 0; i < NUM_TASKS; ++i) pthread_join(tasks[i], NULL);
    pthread_cancel(sched);

    return 0;
}
	

