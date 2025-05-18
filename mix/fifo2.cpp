#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/shm.h>
using namespace std;
int main()
{
const char*fifo ="myfifo";
int fd=open(fifo,O_WRONLY);
int num;
read(fd,&num,sizeof(number));
cout<<"reader received:"<<num<<endl;
close(fd);
unlink(fifo);
return 0;
}
