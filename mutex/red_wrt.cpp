#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
using namespace std;

mutex mtx,red_count;
int count=0,database=100;

void wrt(int id){
mtx.lock();
database+=100;
cout << "Writer " << id << " updated database to: " << database << endl;
    mtx.unlock();
    this_thread::sleep_for(chrono::milliseconds(500));
}
void reader(int id){
red_count.lock();
count++;
if(count==1)
mtx.lock();
red_count.unlock();
cout<<"reader reading "<<id <<" database "<<database<<endl;
    this_thread::sleep_for(chrono::milliseconds(500));
red_count.lock();
count--;
if(count==0){
mtx.unlock();
}
red_count.unlock();
}
int main(){
vector<thread> t1,t2;
t2.emplace_back(wrt,1);
for(int i=1;i<=3;i++){
t1.emplace_back(reader,i);
}
for(auto &t :t1)t.join();
for(auto &t :t2)t.join();
return 0;
}




