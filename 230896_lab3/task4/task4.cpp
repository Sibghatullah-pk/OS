#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t pid = fork();

    if (pid == 0) {  
        cout << "Child (PID: " << getpid() << ") created, now exiting.\n";
        exit(0); 
    } else if (pid > 0) {  
               cout << "Parent (PID: " << getpid() << ") sleeping for 10 seconds...\n";
        sleep(10);    
        cout << "Parent: Child process " << pid << " is now a zombie\n";

               pid_t zombie_pid = wait(NULL);
        cout << "Parent: Cleaned up zombie child (PID: " << zombie_pid << ")\n";
    } else {
        cerr << "Error: Fork failed!\n";
        exit(1);
    }

    return 0;
}
