#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<cstdlib>
using namespace std;
 void* roll_disc(void*agr){
 int value=(rand()%6)+1;
 int * result=(int*)malloc(sizeof(int));
 if(result==NULL)
 {
 cout<<"alocation failed"<<endl;
 return NULL;
 }
 *result=value;
 return (void*)result;
 }
 int main()
 {
 int* res;
 srand(time(NULL));
 
 pthread_t th;
 if(pthread_create(&th,NULL,roll_disc,NULL)!=0){
   cout << "Thread creation failed!" << endl;
        return 1;
    }
   if (pthread_join(th, (void**)&res) != 0) {
        cout << "Thread join failed!" << endl;
        return 2;
    }
if(res!=NULL){
cout<<"result is:"<<*res<<endl;
free(res);
}
else
{
cout<<"no result returned"<<endl;
}
return 0;
}
 
 
 
 
 
 
 
 
 
 
 
