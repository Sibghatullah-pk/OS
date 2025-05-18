#include<iostream>
#include<unistd.h>
#include<pthread.h>
using namespace std;
void * routine(void* arg){
cout<<"testing"<<endl;
return NULL;
}

int main()
{
pthread_t t;
int result=pthread_create(&t,NULL,routine,NULL);
if(result!=0)
{
cout<<"thread failed"<<endl;
return 1;
}
result=pthread_join(t,NULL);

if(result!=0)
{
cout<<"failed join"<<endl;
return 1;
}
cout<<"main thread terminating"<<endl;
return 0;
}

