#include <iostream>
#include <unistd.h>
#include<sys/wait.h>
#include <cstdlib>
using namespace std;
int main() {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0) {
( char *envp[] = {
(char *)"MY_VAR1=Hello",
(char *)"MY_VAR2=World",
(char *)"MY_VAR3=12345",
(char *)NULL
};
cout << "Child process printing environment variables:" << endl;
cout << "MY_VAR1: " << getenv("MY_VAR1") << endl;
cout << "MY_VAR2: " << getenv("MY_VAR2") << endl;
cout << "MY_VAR3: " << getenv("MY_VAR3") << endl;
execle("/bin/echo", "echo", "Environment variables passed to new program:", (char *)NULL, envp);
perror("execle failed");
exit(1);
} else {
wait(NULL);
cout << "Parent process finished" << endl;
}
return 0;
}
