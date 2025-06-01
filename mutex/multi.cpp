#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include<chrono>
using namespace std;

mutex cpu,ram,storage,output;

bool try_lock(mutex& m1,mutex& m2,mutex& m3,int time){
while (1) {
        if (m1.try_lock() && m2.try_lock() && m3.try_lock()) {
            return true;
        }
        this_thread::sleep_for(chrono::milliseconds(10));
    }
    return false;
    }
  void assign_task(int id){
  for(int i=0;i<3;i++){
  if(try_lock(cpu,ram,storage,1000)){
  output.lock();
cout << "Thread " << id << " assigned task " << i + 1 << " with CPU, RAM, and Storage" << endl;
  output.unlock();
this_thread::sleep_for(chrono::milliseconds(400));
storage.unlock();
ram.unlock();
cpu.unlock();
}
else{
output.lock();
cout << "Thread " << id << " failed to acuiqure resources" << endl;
output.unlock();
this_thread::sleep_for(chrono::milliseconds(200));
}}}
int main(){
vector<thread>t1;
for(int i=0;i<=3;i++){
t1.emplace_back(assign_task,i);
}
for(auto&t:t1)
t.join();
return 0;
}


