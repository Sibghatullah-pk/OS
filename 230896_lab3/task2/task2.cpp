#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main() {

pid_t pid1,pid2;
int status ;
pid1=fork();
if(pid1==0)
{
cout<<"child1 pid"<<getpid()<<"exiting with code(0)\n";
exit(0);
}
pid2=fork();
if(pid2==0)
{
cout<<"child2 pid"<<getpid()<<"exiting with code(1)\n";
exit(1);
}

for(int i=0;i<2;i++)
{
pid_t child_pid=wait(&status);
if(WIFEXITED(status))
{
cout<<"parent :child(pid:"<<child_pid<<")exited with status"<<WEXITSTATUS(status)<<"\n";
}
}
return 0;
}
