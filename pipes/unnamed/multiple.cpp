#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
using namespace std;
int main()
{
const int N_child=3;
int fd[2];

if(pipe(fd)==-1)
{
cerr<<"pipe failed"<<endl;
return 1;
}

for(int i=0;i<N_child;i++)
{
pid_t pid=fork();
if(pid<0)
{
cerr<<"fork failed"<<endl;
return 1;
}

if(pid==0)
{
close(fd[0]);

string msg="data from child"+to_string(i)+"\n";
write(fd[1],msg.c_str(),msg.length());
cout<<"child"<<i<<"send"<<msg;
close(fd[1]);
exit(0);
}
}
close(fd[1]);
char buffer[1024];
int total_bytes=0;
cout<<"parent is reading from pipe"<<endl;

while(total_bytes<N_child*20)
{
int bytes_read=read(fd[0],buffer+total_bytes,sizeof(buffer)-total_bytes-1);
if(bytes_read>0)
{
total_bytes+=bytes_read;
buffer[total_bytes]='\0';
}
}

cout << "Parent received:\n" << buffer;

    close(fd[0]);
    for (int i = 0; i < N_child; i++) {
        wait(nullptr);
    }

    return 0;
}
