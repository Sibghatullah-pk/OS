#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main() {
    int arr[4] = {10, 5, 8, 3};
    int pipefd1[2], pipefd2[2];
cout << "sorted parent array: " << arr[0] << " " << arr[1] << " " << arr[2] << " " << arr[3] << endl;
    if (pipe(pipefd1) == -1 || pipe(pipefd2) == -1) {
        cerr << "Pipe problem!\n";
        return 1;
    }

    pid_t p_id1 = fork();
    if (p_id1 == 0) {
        close(pipefd1[0]);
        write(pipefd1[1], arr, 2 * sizeof(int));
        close(pipefd1[1]);
        exit(0);
    }

    pid_t p_id2 = fork();
    if (p_id2 == 0) {
        close(pipefd2[0]);
        write(pipefd2[1], arr + 2, 2 * sizeof(int));
        close(pipefd2[1]);
        exit(0);
    }

    close(pipefd1[1]);
    close(pipefd2[1]);

    int part1[2], part2[2];
    read(pipefd1[0], part1, 2 * sizeof(int));
    read(pipefd2[0], part2, 2 * sizeof(int));

    close(pipefd1[0]);
    close(pipefd2[0]);

    waitpid(p_id1, nullptr, 0);
    waitpid(p_id2, nullptr, 0);

    cout << "Part 1: " << part1[0] << " " << part1[1] << endl;
    cout << "Part 2: " << part2[0] << " " << part2[1] << endl;

    return 0;
}
