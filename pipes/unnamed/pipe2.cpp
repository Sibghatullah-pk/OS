#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

using namespace std;

int main()
{
    int fd[2], fd1[2];

    // Create both pipes and check for errors
    if ((pipe(fd) == -1) || (pipe(fd1) == -1))
    {
        cout << "Error while creating pipes" << endl;
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        cout << "Fork failed" << endl;
        return 1;
    }
while(running){
    if (pid == 0) // Child process
    {
        close(fd[1]); // Close write end of fd (parent → child)
        close(fd1[0]); // Close read end of fd1 (child → parent)

        // Read message from parent
        char buffer[100];
        int bytes_read = read(fd[0], buffer, sizeof(buffer) - 1);
        if (bytes_read > 0)
        {
            buffer[bytes_read] = '\0'; // Null-terminate string
            cout << "Child received: " << buffer << endl;
        }
        close(fd[0]); // Close read end of fd

        // Child sends message to parent
        const char *message = "Message from child";
        write(fd1[1], message, strlen(message) + 1);
        cout << "Child sent: " << message << endl;

        close(fd1[1]); // Close write end of fd1
    }
    if(
    }
    else // Parent process
    {
        close(fd[0]); // Close read end of fd
        close(fd1[1]); // Close write end of fd1

        // Parent sends message to child
        const char *message = "Hello from parent";
        write(fd[1], message, strlen(message) + 1);
        cout << "Parent sent: " << message << endl;
        close(fd[1]); // Close write end of fd

        // Parent reads message from child
        char buffer[100];
        int bytes_read = read(fd1[0], buffer, sizeof(buffer) - 1);
        if (bytes_read > 0)
        {
            buffer[bytes_read] = '\0';
            cout << "Parent received: " << buffer << endl;
        }
        close(fd1[0]); // Close read end of fd1

        wait(NULL); // Parent waits for child to finish
    }

    return 0;
}

