#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
mutex mtx;
int count=0;

void inc(int id){
for(int i=0;i<1000;i++){
mtx.lock();
count++;
mtx.unlock();
}cout<<"thread: "<<id<<"done"<<endl;
}
int main(){
thread t1(inc,1);
thread t2(inc,2);
t1.join();t2.join();
cout<<"final count: "<<count<<endl;
return 0;
}
