//Ek program likho jisme 3 threads (low, medium, high priority) ek shared resource ka use karte hain. Low priority thread resource lock kar leta hai, lekin high priority thread usay preempt kar deta hai—priority inversion hota hai. Mutex ka use karke issue solve karo.

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex mtx;
mutex output_mtx;
int resource = 0;
bool resource_in_use = false;
int current_priority = 0;

void lock_based_on_priority(int id, int priority) {
    while (true) {
        if (!resource_in_use || priority > current_priority) {
            mtx.lock();
            resource_in_use = true;
            current_priority = priority;
            break;
        } else {
            this_thread::sleep_for(chrono::milliseconds(100)); // wait and retry
        }
    }
}

void unlock_resource() {
    resource_in_use = false;
    current_priority = 0;
    mtx.unlock();
}

void task(const string& name, int priority, int work) {
    lock_based_on_priority(priority, priority);
    {
        lock_guard<mutex> lock(output_mtx);
        cout << name << " locked resource with priority " << priority << endl;
    }

    resource += work;
    this_thread::sleep_for(chrono::milliseconds(500));

    {
        lock_guard<mutex> lock(output_mtx);
        cout << name << " updated resource to " << resource << endl;
    }

    unlock_resource();
}

int main() {
    thread t1(task, "Low Priority", 1, 10);
    this_thread::sleep_for(chrono::milliseconds(100)); // Let low start
    thread t2(task, "High Priority", 3, 50);
    thread t3(task, "Medium Priority", 2, 20);

    t1.join();
    t2.join();
    t3.join();

    cout << "Final resource value: " << resource << endl;
    return 0;
}

