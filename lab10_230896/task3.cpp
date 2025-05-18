#include<iostream>
#include<pthread.h>
#include<semaphore.h>
using namespace std;
sem_t readSem;
sem_t writeSem;
int readers=0;
int x=0;
void* reader(void* arg){
sem_wait(&readSem);
readers++;
if(readers==1){
sem_wait(&writeSem);
}
sem_post(&readSem);
cout<<"Reader reads x: "<<x<<endl;
sem_wait(&readSem);
readers--;
if(readers==0){
sem_post(&writeSem);
}
sem_post(&readSem);
return nullptr;
}
void* writer(void* arg){
sem_wait(&writeSem);
x++;
cout<<"Writer updates x to: "<<x<<endl;
sem_post(&writeSem);
return nullptr;
}
int main(){
pthread_t r[5],w[2];
sem_init(&readSem,0,1);
sem_init(&writeSem,0,1);
for(int i=0;i<5;i++){
pthread_create(&r[i],nullptr,reader,nullptr);
}
for(int i=0;i<2;i++){
pthread_create(&w[i],nullptr,writer,nullptr);
}
for(int i=0;i<5;i++){
pthread_join(r[i],nullptr);
}
for(int i=0;i<2;i++){
pthread_join(w[i],nullptr);
}
sem_destroy(&readSem);
sem_destroy(&writeSem);
return 0;
}

