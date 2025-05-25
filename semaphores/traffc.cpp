//Ek intersection pe do roads hain (North-South aur East-West). Ek time pe sirf ek road ka traffic ja sakta hai. Semaphore ka use karke manage karo.
#include<iostream>
#include<thread>
#include<semaphore.h>
#include<vector>
#include<unistd.h>
using namespace std;

sem_t trf_sem;

void control(string direct)
{
while(true){
sem_wait(&trf_sem);
cout<<direct<<"traffic allowed"<<endl;
this_thread::sleep_for(chrono::seconds(2));
cout<<direct<<"traffic stopped"<<endl;
sem_post(&trf_sem);
this_thread::sleep_for(chrono::seconds(1));
}}
int main(){
sem_init(&trf_sem,0,1);

thread NtoS(control,"north-south");
thread EtoW(control,"east-west");
NtoS.join();
EtoW.join();

sem_destroy(&trf_sem);
return 0;
}



