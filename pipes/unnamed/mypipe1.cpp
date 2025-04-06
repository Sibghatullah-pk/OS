#include<iostream>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/types.h>
#include<string>
using namespace std;
int main ()
{

int fd =mkfifo("mypipe",0666);
fd= open("mypipe",O_WRONLY);

string message = "HEllo , How are u?";
write (fd,message.c_str(),message.size() +1);
close(fd);
return 0;
}


