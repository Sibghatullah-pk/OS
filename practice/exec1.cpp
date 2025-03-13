#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
using namespace std;

int main()
{
pid_t pid[3];
const char* command[3][3] = {
        {"/bin/ls", "ls", "-l"},
        {"/bin/pwd", "pwd", NULL},
        {"/usr/bin/whoami", "whoami", NULL}
    };
for(int i=0;i<3;i++)
{
pid[i]=fork();
if(pid[i]==0)
{
execl(command[i][0],command[i][1],command[i][2],NULL);
cerr<<"exec failed"<<i<<"\n";
exit(1);
}
else if(pid[i]<0)
{
cerr<<"fork failed\n";
return 1;
}
else
{
waitpid(pid[i], NULL, 0);
        std::cout << "Command " << i << " done\n";
    }
}
return 0;
}

