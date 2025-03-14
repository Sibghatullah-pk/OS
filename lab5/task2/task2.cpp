#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
using namespace std;

int main() {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        cerr << "Pipe problem!\n";
        return 1;
    }

    pid_t p_id = fork();
    if (p_id == 0) {
        close(pipefd[0]);
        for (int i = 1; i <= 4; ++i) {
            cout << "P sending: " << i << endl;
            write(pipefd[1], &i, sizeof(int));
            sleep(1); // Producer is fast
        }
        close(pipefd[1]);
        exit(0);
    }

    pid_t c_id = fork();
    if (c_id == 0) {
        close(pipefd[1]);
        int num;
        while (read(pipefd[0], &num, sizeof(int)) > 0) {
            cout << "C got: " << num << endl;
            sleep(3); 
        }
        close(pipefd[0]);
        exit(0);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(p_id, nullptr, 0);
    waitpid(c_id, nullptr, 0);

    cout << "All done!\n";
    cout<<"Yeh Producer har 1 second mein cheezein bhejta hai, aur Consumer har 3 second mein unhe padhta hai, lekin pipe ka blocking system problem nahi hone deta—jab tak space ya data nahi milta, woh wait karta hai.";
return 0;
}
