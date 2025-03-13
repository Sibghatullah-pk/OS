#include<iostream>
#include<unistd.h>
#include<sys/wait.h>

using namespace std;

int main()
{
pid_t pid=fork();
if(pid==0)
{
sleep(2);
cout<<"child done";
}
else
{
wait(NULL);
cout<<"parent done";
}
return 0;
}
