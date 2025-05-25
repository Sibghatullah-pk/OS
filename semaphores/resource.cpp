#include<iostream>
#include<thread>
#include<semaphore.h>
#include<vector>
#include<unistd.h>
using namespace std;

sem_t sem;
int numPrn=3;
void print(int id)
{
sem_wait(&sem);
cout<<"printing job"<<id<<" strtd"<<endl;
this_thread::sleep_for(chrono::seconds(1));
cout<<"printing job"<<id<<" completed"<<endl;
sem_post(&sem);
}
int main(){
sem_init(&sem,0,numPrn);
vector<thread>jobs;
for(int i=1;i<=5;i++){
jobs.emplace_back(print,i);
}
for(auto& t:jobs)
t.join();
sem_destroy(&sem);
return 0;
}




