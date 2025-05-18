#include<iostream>
#include<sys/wait.h>
#include<sys/shm.h>
#include<string.h>
using namespace std;

int main(){
int shmid= shmget(IPC_PRIVATE,1024,0666|IPC_CREAT);
char* shared_memory  =(char*)shmat(shmid,NULL,0);
pid_t pid=fork();
if(pid==0){
sleep(1);
cout<<"child read"<<shared_memory<<endl;
shmdt(shared_memory);
exit(0);
}
else if(pid>0){
string msg="shared example";
strcpy(shared_memory,msg.c_str());
cout<<"parent wrote:"<<msg<<endl;
wait(NULL);
shmdt(shared_memory);
shmctl(shmid,IPC_RMID,NULL);
}
else
{
cout<<"fork failed"<<endl;
return 1;
}
return 0;
}
