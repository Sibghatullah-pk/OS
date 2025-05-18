#include<iostream>
#include<pthread.h>
#include<unistd.h>
using namespace std;

int prime[10]={2,3,5,7,11,13,17,19,23,29};
void * routine(void* arg)
{
int index=*(int*)arg;
int sum=0;
for(int i=0;i<5;i++)
{
sum+=prime[index+i];
}
cout<<"thread sum:"<<sum<<endl;
*(int*)arg=sum;
return arg;
}

int main(){
pthread_t th[2];
int i;
for(int i=0;i<2;i++)
{
int *a=(int*)malloc(sizeof(int));
*a=i*5;
if(pthread_create(&th[i],NULL,&routine,a)!=0)
{
return 1;
}
}
int sum=0;
for(int i=0;i<2;i++)
{
int *r;
if(pthread_join(th[i],(void**)&r)!=0)//r value fetch kra ga function wla sa 
{return 2;
}
sum+=*r;
free(r);
}

cout<<"Sum is :"<<sum<<endl;
return 0;
}
