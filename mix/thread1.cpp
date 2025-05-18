#include<iostream>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
using namespace std;

void* grp(void *arg) {
    cout << "Thread: hii\n";
    sleep(20);
    cout << "Thread: finished after 20 seconds\n";
    return NULL;
}

int main() {
    pthread_t var;
    int v;

    cout << "Main: hii\n";
    v = pthread_create(&var, NULL, grp, NULL);
    if (v == 0) {
        cout << "Main: created successfully\n";
    } else {
        cout << "Main: failed\n";
        return 1;
    }

    pthread_join(var, NULL);
    cout << "Main: thread joined, terminating...\n";

    return 0;
}
