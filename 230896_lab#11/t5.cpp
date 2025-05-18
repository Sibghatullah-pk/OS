#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;


const int MAX_PRINTERS = 2;
const int MAX_CPUS = 2;
const int MAX_MEMORY = 3;


sem_t sem_printer;
sem_t sem_cpu;
sem_t sem_memory;

pthread_mutex_t printMutex;

void* process(void* arg) {
    int id = *((int*)arg);

    cout << "Process " << id << " is requesting resources..." << endl << flush;

  
    sem_wait(&sem_printer);
    sem_wait(&sem_cpu);
    sem_wait(&sem_memory);

    pthread_mutex_lock(&printMutex);
    cout << "Process " << id << " got resources [Printer, CPU, Memory]" << endl << flush;
    pthread_mutex_unlock(&printMutex);

    sleep(2); 

    pthread_mutex_lock(&printMutex);
    cout << "Process " << id << " is releasing resources." << endl << flush;
    pthread_mutex_unlock(&printMutex);


    sem_post(&sem_printer);
    sem_post(&sem_cpu);
    sem_post(&sem_memory);

    return NULL;
}

int main() {
    srand(time(0));


    sem_init(&sem_printer, 0, MAX_PRINTERS);
    sem_init(&sem_cpu, 0, MAX_CPUS);
    sem_init(&sem_memory, 0, MAX_MEMORY);
    pthread_mutex_init(&printMutex, NULL);

    const int NUM_PROCESSES = 5;
    pthread_t threads[NUM_PROCESSES];
    int ids[NUM_PROCESSES];

    for (int i = 0; i < NUM_PROCESSES; ++i) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, process, &ids[i]);
        sleep(1); 
    }

    for (int i = 0; i < NUM_PROCESSES; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
	

