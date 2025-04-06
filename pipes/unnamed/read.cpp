#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
using namespace std;

int main(){
int fd =open ("mypipe",O_RDONLY);
char Buffer[100];
read(fd,Buffer,sizeof(Buffer));
cout<<"message: " <<Buffer<<endl;
close(fd);
return 0;
}

