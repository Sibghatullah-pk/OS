#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
using namespace std;

int main() {
    // Variant 1: execl (List-based, full path, default env)
    pid_t pid1 = fork();
    if (pid1 == 0) {
        cout << "Child 1: Using execl to run 'ls -l'..." << endl;
        execl("/bin/ls", "ls", "-l", NULL);
        cout << "Child 1: This won't print if execl succeeds!" << endl;
        exit(1);
    }

    wait(NULL); // Wait for Child 1

    // Variant 2: execv (Vector-based, full path, default env)
    pid_t pid2 = fork();
    if (pid2 == 0) {
        cout << "Child 2: Using execv to run 'ls -l'..." << endl;
        char *args[] = {(char*)"ls", (char*)"-l", NULL};
        execv("/bin/ls", args);
        cout << "Child 2: This won't print if execv succeeds!" << endl;
        exit(1);
    }

    wait(NULL); // Wait for Child 2

    // Variant 3: execlp (List-based, PATH search, default env)
    pid_t pid3 = fork();
    if (pid3 == 0) {
        cout << "Child 3: Using execlp to run 'ls -l'..." << endl;
        execlp("ls", "ls", "-l", NULL);
        cout << "Child 3: This won't print if execlp succeeds!" << endl;
        exit(1);
    }

    wait(NULL); // Wait for Child 3

    // Variant 4: execvp (Vector-based, PATH search, default env)
    pid_t pid4 = fork();
    if (pid4 == 0) {
        cout << "Child 4: Using execvp to run 'ls -l'..." << endl;
        char *args[] = {(char*)"ls", (char*)"-l", NULL};
        execvp("ls", args);
        cout << "Child 4: This won't print if execvp succeeds!" << endl;
        exit(1);
    }

    wait(NULL); // Wait for Child 4

    // Variant 5: execle (List-based, full path, custom env)
    pid_t pid5 = fork();
    if (pid5 == 0) {
        cout << "Child 5: Using execle to run 'ls -l' with custom env..." << endl;
        char *env[] = {(char*)"USER=guest", (char*)"PATH=/bin", NULL};
        execle("/bin/ls", "ls", "-l", NULL, env);
        cout << "Child 5: This won't print if execle succeeds!" << endl;
        exit(1);
    }

    wait(NULL); // Wait for Child 5

    // Variant 6: execve (Vector-based, full path, custom env)
    pid_t pid6 = fork();
    if (pid6 == 0) {
        cout << "Child 6: Using execve to run 'ls -l' with custom env..." << endl;
        char *args[] = {(char*)"ls", (char*)"-l", NULL};
        char *env[] = {(char*)"USER=guest", (char*)"PATH=/bin", NULL};
        execve("/bin/ls", args, env);
        cout << "Child 6: This won't print if execve succeeds!" << endl;
        exit(1);
    }

    wait(NULL); // Wait for Child 6

    cout << "Parent: All children finished!" << endl;
    return 0;
}
