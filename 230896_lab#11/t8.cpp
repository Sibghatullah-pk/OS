#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int NUM_CHAIRS = 3;
const int NUM_CUSTOMERS = 10;
const int NUM_BARBERS = 2;

sem_t customers;
sem_t barbers;
pthread_mutex_t waitingRoomMutex;
int waitingCustomers = 0;

void* barber(void* arg) {
    int id = *((int*)arg);
    while (true) {
        sem_wait(&customers); // wait for a customer

        pthread_mutex_lock(&waitingRoomMutex);
        waitingCustomers--;
        cout << "Barber " << id << " is cutting hair. Waiting customers: " << waitingCustomers << endl << flush;
        pthread_mutex_unlock(&waitingRoomMutex);

        sem_post(&barbers); // barber is ready
        sleep(3); // simulate haircut time
    }
    return NULL;
}

void* customer(void* arg) {
    int id = *((int*)arg);

    pthread_mutex_lock(&waitingRoomMutex);
    if (waitingCustomers < NUM_CHAIRS) {
        waitingCustomers++;
        cout << "Customer " << id << " is waiting. Waiting customers: " << waitingCustomers << endl << flush;
        pthread_mutex_unlock(&waitingRoomMutex);

        sem_post(&customers); // notify a customer is ready
        sem_wait(&barbers);  // wait for barber

        cout << "Customer " << id << " is getting a haircut." << endl << flush;
    } else {
        cout << "Customer " << id << " left (no chair available)." << endl << flush;
        pthread_mutex_unlock(&waitingRoomMutex);
    }

    return NULL;
}

int main() {
    srand(time(0));

    sem_init(&customers, 0, 0);
    sem_init(&barbers, 0, 0);
    pthread_mutex_init(&waitingRoomMutex, NULL);

    pthread_t barberThreads[NUM_BARBERS];
    int barberIds[NUM_BARBERS];

    for (int i = 0; i < NUM_BARBERS; ++i) {
        barberIds[i] = i + 1;
        pthread_create(&barberThreads[i], NULL, barber, &barberIds[i]);
    }

    pthread_t customerThreads[NUM_CUSTOMERS];
    int customerIds[NUM_CUSTOMERS];

    for (int i = 0; i < NUM_CUSTOMERS; ++i) {
        customerIds[i] = i + 1;
        pthread_create(&customerThreads[i], NULL, customer, &customerIds[i]);
        sleep(1); // stagger customer arrival
    }

    for (int i = 0; i < NUM_CUSTOMERS; ++i) pthread_join(customerThreads[i], NULL);

    // Optional: cancel barbers after all customers served
    for (int i = 0; i < NUM_BARBERS; ++i) pthread_cancel(barberThreads[i]);

    return 0;
}

	

