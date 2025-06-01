#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

mutex mtx;
int balance = 1000;

void deposit(int id, int amt) {
    mtx.lock();
    balance += amt;
    cout << "Thread " << id << " added " << amt << ", new balance: " << balance << endl;
    mtx.unlock();
    this_thread::sleep_for(chrono::milliseconds(100));
}

void withdraw(int id, int amt) {
    mtx.lock();
    if (balance >= amt) {
        balance -= amt;
        cout << "Thread " << id << " withdrew " << amt << ", new balance: " << balance << endl;
    } else {
        cout << "Thread " << id << " failed to withdraw " << amt << ", insufficient balance: " << balance << endl;
    }
    mtx.unlock();
    this_thread::sleep_for(chrono::milliseconds(100));
}

int main() {
    int depAmt, withAmt;

    cout << "Enter amount to deposit: ";
    cin >> depAmt;

    cout << "Enter amount to withdraw: ";
    cin >> withAmt;

    thread t1(deposit, 1, depAmt);
    thread t2(withdraw, 2, withAmt);

    t1.join();
    t2.join();

    return 0;
}

