#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void threadFunction(int num) {
    cout << "I am thread No. " << num << " with thread id " << this_thread::get_id() << endl;
}

int main() {
    const int N = 5; // you can change N to anything
    thread threads[N]; // simple array of threads

    // Create all threads
    for (int i = 0; i < N; i++) {
        threads[i] = thread(threadFunction, i + 1);
    }

    // Group 1: {1, 4}
    cout << "After 1 second\n";
    this_thread::sleep_for(chrono::seconds(1));
    if (N >= 1) threads[0].join(); // thread 1
    if (N >= 4) threads[3].join(); // thread 4

    // Group 2: {2, 5}
    cout << "\nAfter 2 seconds\n";
    this_thread::sleep_for(chrono::seconds(1));
    if (N >= 2) threads[1].join(); // thread 2
    if (N >= 5) threads[4].join(); // thread 5

    // Group 3: {3}
    cout << "\nAfter 3 seconds\n";
    this_thread::sleep_for(chrono::seconds(1));
    if (N >= 3) threads[2].join(); // thread 3

    cout << "\nMain thread terminating...\n";
    return 0;
}
