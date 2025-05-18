#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

int balanceAccount1 = 1000;
int balanceAccount2 = 1000;

pthread_mutex_t accountLock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t accountLock2 = PTHREAD_MUTEX_INITIALIZER;

void* transfer1(void* arg) {
    // Lock accounts in a fixed order to avoid deadlock
    pthread_mutex_lock(&accountLock1);
    cout << "Transaction 1: Locked Account 1\n";
    usleep(100000);
    pthread_mutex_lock(&accountLock2);
    cout << "Transaction 1: Locked Account 2\n";
    balanceAccount1 -= 100;
    balanceAccount2 += 100;
    cout << "Transaction 1: Transferred 100 from Account 1 to Account 2\n";
    pthread_mutex_unlock(&accountLock2);
    pthread_mutex_unlock(&accountLock1);
    return nullptr;
}

void* transfer2(void* arg) {
    // Lock accounts in the same order as transfer1 to avoid deadlock
    pthread_mutex_lock(&accountLock1);
    cout << "Transaction 2: Locked Account 1\n";
    usleep(100000);
    pthread_mutex_lock(&accountLock2);
    cout << "Transaction 2: Locked Account 2\n";
    balanceAccount2 -= 100;
    balanceAccount1 += 100;
    cout << "Transaction 2: Transferred 100 from Account 2 to Account 1\n";
    pthread_mutex_unlock(&accountLock2);
    pthread_mutex_unlock(&accountLock1);
    return nullptr;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, nullptr, transfer1, nullptr);
    pthread_create(&t2, nullptr, transfer2, nullptr);
    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    cout << "Final Balance of Account 1: " << balanceAccount1 << endl;
    cout << "Final Balance of Account 2: " << balanceAccount2 << endl;
    pthread_mutex_destroy(&accountLock1);
    pthread_mutex_destroy(&accountLock2);
    return 0;
}
