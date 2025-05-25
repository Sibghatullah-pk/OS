#include<iostream>
#include<thread>
#include<semaphore.h>
#include<vector>
using namespace std;
sem_t printer1,printer2,scanner;
void task(int id) {
    if (id == 1) {
        sem_wait(&printer1); // Lock in order: printer1, scanner
        cout << "T1 acquired Printer 1" << endl;
        sem_wait(&scanner);
        cout << "T1 acquired Scanner" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        sem_post(&scanner);
        sem_post(&printer1);
        cout << "T1 released resources" << endl;
    } else if (id == 2) {
        sem_wait(&printer2); // Lock in order: printer2, scanner
        cout << "T2 acquired Printer 2" << endl;
        sem_wait(&scanner);
        cout << "T2 acquired Scanner" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        sem_post(&scanner);
        sem_post(&printer2);
        cout << "T2 released resources" << endl;
    } else if (id == 3) {
        sem_wait(&printer1); // Lock printer1 first
        cout << "T3 acquired Printer 1" << endl;
        sem_wait(&printer2);
        cout << "T3 acquired Printer 2" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        sem_post(&printer2);
        sem_post(&printer1);
        cout << "T3 released resources" << endl;
    }
}

int main() {
    sem_init(&printer1, 0, 1);
    sem_init(&printer2, 0, 1);
    sem_init(&scanner, 0, 1);

    vector<thread> threads;
    threads.emplace_back(task, 1);
    threads.emplace_back(task, 2);
    threads.emplace_back(task, 3);

    for (auto& t : threads) t.join();

    sem_destroy(&printer1);
    sem_destroy(&printer2);
    sem_destroy(&scanner);

    return 0;
}
