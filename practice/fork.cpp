#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
using namespace std;

int main()
{
execlp("ping","ping","google.com",NULL);
//execlp("fork1.cpp",fork1,(char*)NULL;
cout<<"hii";

}
