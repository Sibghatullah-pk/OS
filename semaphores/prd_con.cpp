#include<iostream>
#include<semaphore.h>
#include<thread>
using namespace std;

 int siz=5;
sem_t empt,full,semp;
void producer()
{
for(int i=0;i<5;i++)
{
sem_wait(&empt);
sem_wait(&semp);
cout<<"produced"<<i<<endl;
sem_post(&full);
sem_post(&semp);
this_thread::sleep_for(chrono::milliseconds(500));
}
}
void consumer()
{
for(int i=0;i<5;i++)
{
sem_wait(&full);
sem_wait(&semp);
cout<<"waiting for production"<<i<<endl;
cout<<"consumed"<<endl;
sem_post(&semp);
sem_post(&empt);
this_thread::sleep_for(chrono::milliseconds(500));
}
}
int main(){
sem_init(&semp,0,1);
sem_init(&empt,0,siz);//initailly filled slot euql to size jo k 5 hn
sem_init(&full,0,0);//initailly filled slot zero hn
thread t1(producer),t2(consumer);
t1.join();
t2.join();
sem_destroy(&semp);
sem_destroy(&empt);
sem_destroy(&full);
return 0;
}


