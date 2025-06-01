//Question: Dining Philosophers problem implement karo jisme 5 philosophers hain, aur har ek ke paas ek fork hai (total 5 forks). Mutex ka use karke deadlock aur starvation avoid karo.
//🔍 Core Idea
//5 philosophers sit around a table.
//Each needs 2 forks (left and right) to eat.
//After eating, they put down the forks and think.
//This repeats for 3 rounds per philosopher.
// Dining Philosophers Problem: Avoid Deadlock and Starvation using Mutex

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;

const int n = 5;
mutex forks[n], out_mtx;

void phil(int id) {
    int left = id;
    int right = (id + 1) % n;

    for (int i = 0; i < 3; i++) {
        // Pick forks in a consistent order to avoid deadlock
        if (left < right) {
            forks[left].lock();
            forks[right].lock();
        } else {
            forks[right].lock();
            forks[left].lock();
        }

        out_mtx.lock();
        cout << "Philosopher " << id << " is eating (round " << i + 1 << ")" << endl;
        out_mtx.unlock();
        this_thread::sleep_for(chrono::milliseconds(200));

        forks[left].unlock();
        forks[right].unlock();

        out_mtx.lock();
        cout << "Philosopher " << id << " is thinking" << endl;
        out_mtx.unlock();
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

int main() {
    vector<thread> philos;
    for (int i = 0; i < n; i++) {
        philos.emplace_back(phil, i);
    }

    for (auto& t : philos)
        t.join();

    return 0;
}

