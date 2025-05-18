#include<iostream>
#include<thread>
using namespace std;

void threadFuntion(int num)
{
cout<<"i am thread numbr"<<num<<"with id"<<this_thread::get_id()<<endl;
}
int main()
{
thread t1(threadFuntion,1);
thread t2(threadFuntion,2);
t1.join();
t2.join();
cout<<"main thread terminating ..\n";
return 0;
}

