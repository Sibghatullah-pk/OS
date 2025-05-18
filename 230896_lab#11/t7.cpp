#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int NUM_FLOORS = 5;
const int NUM_PASSENGERS = 5;

sem_t floorSem[NUM_FLOORS];
sem_t elevator; // binary semaphore for elevator access

void* passenger(void* arg) {
    int id = *((int*)arg);
    int floor = rand() % NUM_FLOORS;

    cout << "Passenger " << id << " is waiting on floor " << floor << endl << flush;
    sem_wait(&floorSem[floor]); // wait for elevator on the floor

    sem_wait(&elevator); // enter elevator
    cout << "Passenger " << id << " has entered the elevator at floor " << floor << endl << flush;

    sleep(2); // simulate travel time

    cout << "Passenger " << id << " has exited the elevator." << endl << flush;
    sem_post(&elevator); // leave elevator

    return NULL;
}

void* elevatorController(void* arg) {
    while (true) {
        for (int floor = 0; floor < NUM_FLOORS; ++floor) {
            cout << "Elevator arriving at floor " << floor << endl << flush;
            sem_post(&floorSem[floor]); // signal elevator is at this floor
            sleep(3); // elevator stays briefly at each floor
        }
    }
    return NULL;
}

int main() {
    srand(time(0));

    sem_init(&elevator, 0, 1);
    for (int i = 0; i < NUM_FLOORS; ++i) {
        sem_init(&floorSem[i], 0, 0);
    }

    pthread_t passengers[NUM_PASSENGERS];
    pthread_t controller;
    int ids[NUM_PASSENGERS];

    pthread_create(&controller, NULL, elevatorController, NULL);

    for (int i = 0; i < NUM_PASSENGERS; ++i) {
        ids[i] = i + 1;
        pthread_create(&passengers[i], NULL, passenger, &ids[i]);
        sleep(1); // stagger passenger arrivals
    }

    for (int i = 0; i < NUM_PASSENGERS; ++i) pthread_join(passengers[i], NULL);
    pthread_cancel(controller);

    return 0;
}

	

