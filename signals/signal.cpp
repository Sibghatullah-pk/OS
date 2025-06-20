#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<sys/wait.h>
using namespace std;

int main(){
int pid=fork();
if(pid==-1){
return 1;
}
if(pid==0){
while(1){
cout<<"hiii"<<endl;
usleep(50000);
}
}
else{
sleep(1);
kill(pid,SIGKILL);
wait(NULL);
}
 
return 0;
}

