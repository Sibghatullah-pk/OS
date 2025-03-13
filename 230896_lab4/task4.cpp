#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

int main() {
    pid_t pid1, pid2;

    pid1 = fork();
    if (pid1 == -1) {
        perror("fork failed for first child");
        exit(1);
    }

    if (pid1 == 0) {
        cout << "in child 1:" << endl;
        execlp("ls", "ls", "-l", (char*)NULL);
        cerr << "failed to execute ls in child 1" << endl;
        exit(1);
    } else {
        pid2 = fork();
        if (pid2 == -1) {
            perror("fork failed for second child");
            exit(1);
        }

        if (pid2 == 0) {
            cout << "Child 2: Executing 'date'..." << endl;
            execlp("date", "date", (char*)NULL);
            perror("execlp failed for second child");
            exit(1);
        }
    }

    int status1, status2;
    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);

    if (WIFEXITED(status1)) {
        cout << "Child 1 exited with status " << WEXITSTATUS(status1) << endl;
    } else {
        cout << "Child 1 terminated abnormally" << endl;
    }

    if (WIFEXITED(status2)) {
        cout << "Child 2 exited with status " << WEXITSTATUS(status2) << endl;
    } else {
        cout << "Child 2 terminated abnormally" << endl;
    }

    cout << "Parent process finished" << endl;

    return 0;
}
