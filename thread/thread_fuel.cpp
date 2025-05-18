#include<iostream>
#include<pthread.h>
#include<unistd.h>
using namespace std;
pthread_mutex_t mutexfuel;
int fuel=0;
void* fuelfilling(void*arg){
for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutexfuel);
        fuel += 15;
        std::cout << "Filled fuel... " << fuel << std::endl;
        pthread_mutex_unlock(&mutexfuel);
        sleep(1);
    }
    return nullptr;
}
void* car(void*arg)
{
while(true)
{
pthread_mutex_lock(&mutexfuel);
if(fuel>=40){
fuel-=40;
cout<<"got fuel.bye.."<<endl;
pthread_mutex_unlock(&mutexfuel);
break;
}
else {
cout << "No fuel. Waiting...\n";
pthread_mutex_unlock(&mutexfuel); 
sleep(1); 
 }
 }
 return NULL;
 }
int main()
{
pthread_t th[2];
  if(pthread_mutex_init(&mutexfuel,NULL)!=0)
  {
    cout<<"mutex failed"<<endl;
    return 1;
  }
  if(pthread_create(&th[0],NULL,car,NULL)!=0)
  {
    cout<<"thread 1 car :failed"<<endl;
    return 3;
  }
  if(pthread_create(&th[1],NULL,fuelfilling,NULL)!=0)
  {
    cout<<"thread 2 fuel filling  failed"<<endl;
    return 2;
  }
  
 for(int i=0;i<2;i++){ 
  if(pthread_join(th[i],NULL)!=0)
  {
    cout<<"thread"<<i<<"joinng failed"<<endl;
    return 3;
  }
  }
  
  pthread_mutex_destroy(&mutexfuel);
  return 0;
}
