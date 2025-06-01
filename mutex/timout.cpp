#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

timed_mutex A, B, C;
mutex output_mtx;

bool timeout(timed_mutex& m, int timeout_ms) {
    return m.try_lock_for(chrono::milliseconds(timeout_ms));
}

void task(int id) {
    if (id == 1) {
        if (timeout(A, 1000)) {
            lock_guard<mutex> lock(output_mtx);
            cout << "Thread 1 locked A" << endl;
            if (timeout(B, 1000)) {
                cout << "Thread 1 locked B" << endl;
                if (timeout(C, 1000)) {
                    cout << "Thread 1 locked C" << endl;
                    this_thread::sleep_for(chrono::milliseconds(200));
                    C.unlock();
                } else {
                    cout << "Thread 1 timeout on C" << endl;
                    B.unlock();
                    A.unlock();
                    return;
                }
                B.unlock();
            } else {
                cout << "Thread 1 timeout on B" << endl;
                A.unlock();
                return;
            }
            A.unlock();
        } else {
            cout << "Thread 1 timeout on A" << endl;
        }
    } else {
        if (timeout(C, 1000)) {
            lock_guard<mutex> lock(output_mtx);
            cout << "Thread 2 locked C" << endl;
            if (timeout(B, 1000)) {
                cout << "Thread 2 locked B" << endl;
                if (timeout(A, 1000)) {
                    cout << "Thread 2 locked A" << endl;
                    this_thread::sleep_for(chrono::milliseconds(200));
                    A.unlock();
                } else {
                    cout << "Thread 2 timeout on A" << endl;
                    B.unlock();
                    C.unlock();
                    return;
                }
                B.unlock();
            } else {
                cout << "Thread 2 timeout on B" << endl;
                C.unlock();
                return;
            }
            C.unlock();
        } else {
            cout << "Thread 2 timeout on C" << endl;
        }
    }
}

int main() {
    thread t1(task, 1);
    thread t2(task, 2);
    t1.join();
    t2.join();
    return 0;
}

