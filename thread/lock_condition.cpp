#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>

using namespace std;
mutex mtx;
condition_variable cv;

bool data_ready=false;
void producer()
{
this_thread::sleep_for(chrono::seconds(2));
lock_guard<mutex>lock(mtx);
data_ready=true;
cout<<"data produced!"<<endl;
cv.notify_one();
}
void consumer(){
unique_lock<mutex> lock(mtx);
cv.wait(lock,[]{return data_ready;});
cout<<"data cosumed"<<endl;
}
int main(){
thread ct(consumer);
thread pt(producer);
ct.join();
pt.join();
return 0;
}
