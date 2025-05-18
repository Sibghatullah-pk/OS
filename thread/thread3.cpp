#include<iostream>
#include<thread>
#include<pthread.h>
#include<unistd.h>
using namespace std;
void * out(void * arg)
{
cout<<"hii there"<<endl;
sleep(2);
cout<<"thread ending"<<endl;
return NULL;
}
int main()
{
pthread_t t,t1;
int result=pthread_create(&t,NULL,out,NULL);
if(result!=0)
{
cout<<"failed creation";
return 1;
}

result=pthread_create(&t1,NULL,out,NULL);
if(result!=0)
{
cout<<"failed creation";
return 1;
}
result=pthread_join(t,NULL);
if(result!=0)
{
cout<<"failed join";
return 2;
}
result=pthread_join(t1,NULL);
if(result!=0)
{
cout<<"failed join";
return 2;
}
cout<<"all done"<<endl;
return 0;
}

