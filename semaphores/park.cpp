#include<iostream>
#include<thread>
#include<semaphore.h>
#include<vector>

using namespace std;
 sem_t park;
 int total=10;
 void car(int id){
 sem_wait(&park);
 cout<<"car "<<id<<" parked .slot left "<<sem_getvalue(&park, 1)<<endl;
 this_thread::sleep_for(chrono::seconds(1));
    cout << "Car " << id << " leaving." << endl;
    sem_post(&park);
 }
 int main()
 {
 sem_init(&park,0,total);
 vector<thread> cars;
 for(int i=0;i<12;i++){
 cars.emplace_back(car,i);
 }
 for(auto&t:cars)
 t.join();
 sem_destroy(&park);
 return 0;
 }
 
