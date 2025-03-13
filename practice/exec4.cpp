#include<unistd.h>
#include<sys/wait.h>
#include<iostream>
#include<errno.h>

using namespace std;

int main()
{

pid_t childpid=fork();

if(childpid == 0)
{
cout<<"i am child"<<getpid()<<"\n";
execl("home/sibghatullah/Desktop/fork4.cpp", "fork4.cpp",NULL);
cout<<"the next exec()\n";
execl("/home/sibghatullah/Desktop/","ls","-l","/usr",NULL);
cout<<"failed ho ma\n";
}
else if(childpid>0)
{
wait(NULL);
cout<<"\n parent process wit pid"<<getpid();
}
return 0;
}


