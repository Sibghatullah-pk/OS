#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<cstring>
using namespace std;

int main()
{
int pipefd[2];
if(pipe(pipefd)==-1)
{
cerr<<"pipe failed "<<endl;
return 1;
}
pid_t pid=fork();
if(pid==0)
{
close(pipefd[1]);
char buffer[100];
read(pipefd[0],buffer,100);
cout<<"child received   :"<<buffer<<endl;
close(pipefd[0]);
}
else if(pid>0)
{
close(pipefd[0]);
const char* msg="hellow,duniya ";
write(pipefd[1],msg,strlen((msg)+1));
close(pipefd[1]);
wait(NULL);
}
else 
{
cout<<"fork failed"<<endl;
}
return 0;

}
