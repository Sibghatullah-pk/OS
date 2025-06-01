#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
mutex prn,scn;
void task(int id){
if(id==1){
prn.lock();
cout<<"thread 1 aquired printer"<<endl;
this_thread::sleep_for(chrono::milliseconds(10));
prn.unlock();
scn.lock();
cout<<"thread 1 aquired scanner"<<endl;
scn.unlock();
cout<<"thread 1 exixting release resources"<<endl;
}
else{

scn.lock();
cout<<"thread 2 aquired scanner"<<endl;
this_thread::sleep_for(chrono::milliseconds(10));
scn.unlock();
prn.lock();
cout<<"thread 2 aquired printer"<<endl;
prn.unlock();
cout<<"thread 2 exixting release resources"<<endl;
}
}
int main(){
thread t1(task,1);
thread t2(task,2);
t1.join();
t2.join();
return 0;
}

