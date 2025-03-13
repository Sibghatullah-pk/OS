#include<iostream>
#include<sys/wait.h>
#include<unistd.h>
using namespace std;
int main()
{
pid_t pid=fork();
if(pid==0)
{
pid_t pid=fork();
if(pid==0)
{
cout<<"grand childerent here:"<<getpid();
}
else
{
wait(NULL);
cout<<"\ngrand child k parent ho mra bh parent hn";
}

}
else {
wait(NULL);
cout<<"\nall done";
}
return 0;
}
