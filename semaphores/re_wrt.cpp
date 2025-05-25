#include<iostream>
#include<thread>
#include<semaphore.h>
#include<vector>
using namespace std;

sem_t mutex,wrt;
int count=0;
void read(int id){
sem_wait(&mutex);
count++;
if(count==1)
sem_wait(&wrt);
sem_post(&mutex);

cout << "Reader " << id << " is reading." << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << "Reader " << id << " finished reading." << endl;
    sem_wait(&mutex);
    count--;
    if (count == 0) sem_post(&wrt); 
    sem_post(&mutex);
}
void write(int id)
{
sem_wait(&wrt);
cout << "Writer " << id << " is writing." << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "Writer " << id << " finished writing." << endl;
    sem_post(&wrt);
}
int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    vector<thread> readers, writers;
    for (int i = 1; i <= 3; i++) readers.emplace_back(read, i);
    for (int i = 1; i <= 2; i++) writers.emplace_back(write, i);

    for (auto& t : readers) t.join();
    for (auto& t : writers) t.join();

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;

}
