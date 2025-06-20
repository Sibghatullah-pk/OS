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
kill(pid,SIGSTOP);
int t;
do{
cout<<"number of time sec exec";
cin>>t;
 if(t>0){
 kill(pid,SIGCONT);   
 sleep(t);
 kill(pid,SIGSTOP);
 }
}while(t>0);
kill(pid,SIGKILL);
wait(NULL);
}
 
return 0;
}

