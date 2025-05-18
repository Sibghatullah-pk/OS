#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
mutex mtx;
bool data_ready=false;
void producer(){
this_thread::sleep_for(chrono::seconds(2));
mtx.lock();
data_ready=true;
cout<<"data ready"<<endl;
mtx.unlock();
}
void cunsumer(){
while(!data_ready){
this_thread::sleep_for(chrono::seconds(3));
}
mtx.lock();
cout<<"data consumed"<<endl;
mtx.unlock();
}
int main(){
thread ct(cunsumer);
thread pt(producer);
ct.join();
pt.join();
return 0;
}
