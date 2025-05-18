#include<iostream>
#include<pthread.h>
#include<unistd.h>
using namespace std;
 pthread_mutex_t mutex;
void * routine(void*arg)
{
if(pthread_mutex_trylock(&mutex)==0)
{
cout<<"got locked"<<endl;
sleep(1);
pthread_mutex_unlock(&mutex);
}
else
{
cout<<"lock not avaulabe "<<endl;
}
return NULL;
}
int main()
{
pthread_t th[4];
pthread_mutex_init(&mutex,NULL);
for(int i=0;i<4;i++)
{
if(pthread_create(&th[i],NULL,routine,NULL)!=0)
{
cout<<"error while creating"<<endl;
return 2;
}

}
for(int i=0;i<4;i++)
{
if(pthread_join(th[i],NULL)!=0)
{
cout<<"error while joining"<<endl;
return 3;
}
}
pthread_mutex_destroy(&mutex);

return 0;
}





