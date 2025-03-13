#include <iostream>
#include <cstdlib>
#include<sys/wait.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

void executeCommand(const string &command)
{
#ifdef _WIN32
    // Windows-specific code using CreateProcess
    STARTUPINFO si = {sizeof(STARTUPINFO)};
    PROCESS_INFORMATION pi;
    BOOL result = CreateProcess(
        NULL,                   // Application name
        (LPSTR)command.c_str(), // Command line
        NULL,                   // Process handle not inheritable
        NULL,                   // Thread handle not inheritable
        FALSE,                  // Set handle inheritance to FALSE
        0,                      // No creation flags
        NULL,                   // Use parent's environment
        NULL,                   // Use parent's current directory
        &si,                    // Pointer to STARTUPINFO structure
        &pi                     // Pointer to PROCESS_INFORMATION structure
    );

    if (!result)
    {
        cerr << "CreateProcess failed (" << GetLastError() << ")" << endl;
        return;
    }

    WaitForSingleObject(pi.hProcess, INFINITE); // Wait for the process to complete
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
#else
    // Unix-like systems using execvp
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0)
    {
        char *args[] = {(char *)command.c_str(), NULL};
        execvp(args[0], args);
        perror("execvp failed");
        exit(1);
    }
    else
    {
        wait(NULL); // Parent waits for child to finish
    }
#endif
}

int main()
{
    string command;
    cout << "Enter the command to execute: ";
    getline(cin, command);

    executeCommand(command);

    return 0;
}
