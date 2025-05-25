//Ek bounded buffer (size 3) hai, aur 4 producers hain jo items produce karte hain. Semaphores ka use karke overflow avoid karo.
#include<iostream>
#include<thread>
#include<semaphore.h>
#include<vector>
using namespace std;
sem_t semp,empt,full;
const int siz=3;
int buffer[siz];
int in=0;
void producer(int id)
{
for(int i=1;i<=3;i++){
int item=id*10+i;
sem_wait(&empt);
sem_wait(&semp);
buffer[in]=item;
cout << "Producer " << id << " produced: " << buffer[in] << endl;
        in = (in + 1) % siz;
        sem_post(&semp);
        sem_post(&full);
        this_thread::sleep_for(chrono::milliseconds(400));
    }
}

int main()
{
sem_init(&semp,0,1);
sem_init(&empt,0,siz);
sem_init(&full,0,0);
vector<thread> prod;
for(int i=1;i<=4;i++){
prod.emplace_back(producer,i);
}
for(auto& t:prod)
t.join();
sem_destroy(&semp);
sem_destroy(&empt);
sem_destroy(&full);
return 0;
}









