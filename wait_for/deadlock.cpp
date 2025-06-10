//Wait-For Graph (WFG) ek directed graph hai jo multi-threading ya multi-processing systems mein deadlock detection aur avoidance ke liye use hota hai.

#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
mutex r1,r2;
int wfg[2][2]={{0,1},{1,0}};
void task(int id){
if(id==1){
r1.lock();
cout<<"thread 1 locked r1"<<endl;
this_thread::sleep_for(chrono::milliseconds(100));
r2.lock();
cout<<"thread 1 locked r2"<<endl;
r2.unlock();
r1.unlock();
}else{
r2.lock();
cout<<"thread 2 locked r2"<<endl;
this_thread::sleep_for(chrono::milliseconds(100));
r1.lock();
r2.lock();
}}

int main(){
thread t1(task,0);
thread t2(task,1);
t1.join();
t2.join();

cout<<"WFG showa cycle:t1->t2->t1 "<<endl;

return 0;
}

