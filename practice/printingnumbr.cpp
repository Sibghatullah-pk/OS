#include<iostream>
#include <sys/wait.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
using namespace std;

int main()
{

int id=fork();
int status, n;
if(id==0)
{
n=1;
}
else
n=6;

if(id!=0)
{
wait(&status);
}
for(int i=n;i<n+3;i++)
{
cout<<i;
}
if(id!=0)
cout<<"\n";

return 0;
}

