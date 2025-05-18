#include<iostream>
#include<pthread.h>
using namespace std;
int mail=0;
pthread_mutex_t mutex;
void* routine(void* arg)
{
for(int i=0;i<1000000;i++)
{
pthread_mutex_lock(&mutex);
mail++;
pthread_mutex_unlock(&mutex);
}
return NULL;
}

int main(){
 pthread_t t1, t2;
pthread_mutex_init(&mutex,NULL);
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
    return 0;
}
