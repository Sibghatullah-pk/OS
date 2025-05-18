#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void threadFunction(int num) {
    cout << "I am thread No. " << num << " with thread id " <<
 this_thread::get_id() << endl;
}

int main() {
    vector<thread> threads;
    for (int i = 1; i <= 3; i++) {
        threads.emplace_back(threadFunction, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    cout << "Main thread terminating..." << endl;
    return 0;
}
