#include <iostream>
#include <thread>
#include <semaphore.h>
using namespace std;

sem_t sem;
int shared_cntr = 0;

void increment(int id) {
    for (int i = 0; i < 1000; i++) {
        sem_wait(&sem);
        shared_cntr++;
        sem_post(&sem);
    }
    cout << "thread " << id << " done" << endl;
}

int main() {
    sem_init(&sem, 0, 1);
    thread t1(increment, 1);
    thread t2(increment, 2);
    t1.join();
    t2.join();
    cout << "final count: " << shared_cntr << endl;
    sem_destroy(&sem);
    return 0;
}
