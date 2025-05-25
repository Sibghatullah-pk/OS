#include <iostream>
#include <thread>
#include <vector>
#include <semaphore.h>
#include <chrono>

using namespace std;

sem_t semp, empt, full;
const int siz = 5; // Buffer size
const int prod = 3; // Number of producers
const int cons = 2; // Number of consumers
const int items = 5; // Items per producer
int buffer[5]; // Shared buffer array
int in = 0; // Index for producer to insert
int out = 0; // Index for consumer to remove

void producer(int id) {
    for (int i = 1; i <= items; i++) {
        int item = id * 100 + i; // Unique item (e.g., producer 1: 101, 102, ...)
        sem_wait(&empt); // Wait for an empty slot
        sem_wait(&semp); // Acquire mutex
        buffer[in] = item; // Place item in buffer
        cout << "Producer " << id << " produced item " << item << " at index " << in << endl;
        in = (in + 1) % siz; // Circular buffer
        sem_post(&semp); // Release mutex
        sem_post(&full); // Signal a filled slot
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void consumer(int id) {
    for (int i = 1; i <= (prod * items) / cons; i++) {
        sem_wait(&full); // Wait for a filled slot
        sem_wait(&semp); // Acquire mutex
        int item = buffer[out]; // Remove item from buffer
        cout << "Consumer " << id << " consumed item " << item << " from index " << out << endl;
        out = (out + 1) % siz; // Circular buffer
        sem_post(&semp); // Release mutex
        sem_post(&empt); // Signal an empty slot
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int main() {
    sem_init(&semp, 0, 1); // Mutex for buffer access
    sem_init(&empt, 0, siz); // Initially all slots empty
    sem_init(&full, 0, 0); // Initially no slots filled

    vector<thread> t1, t2;

    // Create producer threads
    for (int i = 1; i <= prod; i++) {
        t1.emplace_back(producer, i);
    }

    // Create consumer threads
    for (int i = 1; i <= cons; i++) {
        t2.emplace_back(consumer, i);
    }

    // Join producer threads
    for (auto& t : t1) {
        t.join();
    }

    // Join consumer threads
    for (auto& t : t2) {
        t.join();
    }

    // Clean up semaphores
    sem_destroy(&semp);
    sem_destroy(&empt);
    sem_destroy(&full);

    return 0;
}
