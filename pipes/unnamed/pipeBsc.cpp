#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
using namespace std;
int main()
{
int fd[2];

if(pipe(fd)==-1)
{
cout<<"error while creating pipe";
return 1;
}
pid_t pid=fork();
if(pid<0)
{
cout<<"forkfailed";
return 1;
}
if(pid ==0)
{
close(fd[1]);
char buffer[100];
int bytes_read=read(fd[0],buffer,sizeof(buffer)-1);
if(bytes_read>0)
{
buffer[bytes_read]='\0';
cout<<"child ko yeh msg milla"<<buffer<<endl;
}
close(fd[0]);
}
else
{
close(fd[0]);
const char*message="heelo from parent";
write(fd[1],message,strlen(message)+1);
cout<<"parent nh yh bhja"<<message<<endl;
close(fd[1]);
//wait(NULL);
}
return 0;
}
