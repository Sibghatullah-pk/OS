#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

using namespace std;

int main()
{
    int fd[2], fd1[2];

    // Create pipes and check for errors
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

    if (pid == 0) // Child process
    {
        close(fd[1]); // Close write end of parent-to-child pipe
        close(fd1[0]); // Close read end of child-to-parent pipe

        char buffer[100];
        while (true)
        {
            // Read message from parent
            int bytes_read = read(fd[0], buffer, sizeof(buffer) - 1);
            if (bytes_read > 0)
            {
                buffer[bytes_read] = '\0'; // Null-terminate
                cout << "Child received: " << buffer << endl;

                if (strcmp(buffer, "bye") == 0)
                {
                    cout << "Child exiting..." << endl;
                    break;
                }
            }

            // Child sends a message back
            cout << "Enter message for parent: ";
            cin.getline(buffer, sizeof(buffer));

            write(fd1[1], buffer, strlen(buffer) + 1);

            if (strcmp(buffer, "bye") == 0)
            {
                cout << "Child sent 'bye'. Exiting..." << endl;
                break;
            }
        }

        close(fd[0]);
        close(fd1[1]);
    }
    else // Parent process
    {
        close(fd[0]); // Close read end of parent-to-child pipe
        close(fd1[1]); // Close write end of child-to-parent pipe

        char buffer[100];
        while (true)
        {
            // Parent sends message to child
            cout << "Enter message for child: ";
            cin.getline(buffer, sizeof(buffer));

            write(fd[1], buffer, strlen(buffer) + 1);

            if (strcmp(buffer, "bye") == 0)
            {
                cout << "Parent sent 'bye'. Exiting..." << endl;
                break;
            }

            // Read message from child
            int bytes_read = read(fd1[0], buffer, sizeof(buffer) - 1);
            if (bytes_read > 0)
            {
                buffer[bytes_read] = '\0';
                cout << "Parent received: " << buffer << endl;

                if (strcmp(buffer, "bye") == 0)
                {
                    cout << "Parent exiting..." << endl;
                    break;
                }
            }
        }

        close(fd[1]);
        close(fd1[0]);

        wait(NULL); // Parent waits for child to finish
    }

    return 0;
}

