#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>

using namespace std;
int main()
{

cout<<"listing here\n";
execl("/bin/ls","ls",NULL);
cerr<<"ni chla";
return 1;

}
