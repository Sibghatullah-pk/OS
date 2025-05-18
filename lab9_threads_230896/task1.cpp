#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void threadFunction(int num, int group) {
        this_thread::sleep_for(chrono::seconds(group));
    cout << "I am thread No. " << num << " with thread id " << this_thread::get_id() << endl;
}

int main() {
    int N;
    cout << "Enter N (No. of threads): ";
    cin >> N;
    cout << "Creating " << N << " threads\n";

    thread threads[N]; 

    for (int i = 0; i < N; i++) {
        int group = ( (i+1) % 4 == 0 ) ? 4 : (i+1)%4; 
        threads[i] = thread(threadFunction, i + 1, group);
    }

    for (int group = 1; group <= 4; group++) {
        cout << "\nAfter " << group << " second(s)\n";
        this_thread::sleep_for(chrono::seconds(1));

        for (int i = 0; i < N; i++) {
            int threadGroup = ((i+1) % 4 == 0) ? 4 : (i+1) % 4;
            if (threadGroup == group && threads[i].joinable()) {
                threads[i].join();
            }
        }
    }

    cout << "\nMain was waiting for the threads and is now terminating....\n";
    return 0;
}
