#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* get(void* arg) {
    int index = *(int*)arg;
    cout << "value is: " << primes[index] << endl;
    return NULL;
}

int main() {
    pthread_t td[10];
    int indices[10];

    for (int i = 0; i < 10; i++) {
        indices[i] = i;
        if (pthread_create(&td[i], NULL, get, &indices[i]) != 0) {
            cout << "Thread creation failed for index " << i << endl;
            return 1;
        }
    }

    for (int i = 0; i < 10; i++) {
        if (pthread_join(td[i], NULL) != 0) {
            cout << "Thread join failed for index " << i << endl;
            return 2;
        }
    }

    cout << "All threads completed successfully!" << endl;
    return 0;
}
