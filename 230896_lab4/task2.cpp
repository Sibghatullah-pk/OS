#include<iostream>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/wait.h>  // for wait and waitpid

using namespace std;

int main()
{
    pid_t pid = fork();  // First fork to create the first child process
    if (pid == -1) {
        cerr << "Failed to create first child process." << endl;
        return 1;
    }

    if (pid == 0) {
        // First child: Execute the "hello" program
        execl("./hello", "hello", (char*)NULL);
        cerr << "Failed to execute 'hello' program." << endl;  // If execl fails
        return 1;
    }

    if (pid > 0) {
        // Parent: Wait for the first child to finish
        wait(NULL);
        cout << "First child completed." << endl;
    }

    pid_t pid2 = fork();  // Second fork to create the second child process

    if (pid2 == -1) {
        cerr << "Failed to fork second child." << endl;
        return 1;
    }

    if (pid2 == 0) {
        // Second child: Execute some action (e.g., copying files, etc.)
        // For now, it just exits successfully.
        cout << "Second child copying files..." << endl;
        return 0;  // Exit successfully
    } else {
        // Parent: Wait for the second child to finish
        int status;
        waitpid(pid2, &status, 0);  // Wait for second child process to finish
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            cout << "Second child finished successfully." << endl;
        } else {
            cerr << "Second child failed." << endl;
            return 1;
        }

        cout << "Parent terminating." << endl;
    }

    return 0;
}
