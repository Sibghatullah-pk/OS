#include<iostream>
#include<pthread.h>
using namespace std;
int mail=0;
bool lock=0;
void* routine(void* arg)
{
//mail++;// till now no race condition still agin lets move to loop
for(int i=0;i<1000000;i++)
{
if(lock==1)
{
wait();
}
lock=1;
mail++;//answer should be like 2000000 but its diffrent that called
// race condition thek hn
lock=0;
}
return NULL;
}

int main(){
 pthread_t t1, t2;
    if (pthread_create(&t1, NULL, &routine, NULL)) {
        return 1;
    }
    if (pthread_create(&t2, NULL, &routine, NULL)) {
        return 2;
    }
    if (pthread_join(t1, NULL)) {
        return 3;
    }
    if (pthread_join(t2, NULL)) {
        return 3;
    }
cout<<"number of mails"<<mail<<endl;
pthread_mutex_destroy(&mutex);
    return 0;
}
