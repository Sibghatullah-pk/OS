#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
using namespace std;

const int KIDS = 3;

pid_t kid_ids[KIDS];
int start_nums[KIDS];  
int finish[KIDS];
int work_time[KIDS];



int main() {
    
    srand(time(NULL));

    
    int pipefd[KIDS * 2];

    
    for (int i = 0; i < KIDS; ++i) {
        if (pipe(&pipefd[i * 2]) == -1) {
            cerr << "Pipe problem!\n";
            return 1;
        }
    }

    
    for (int i = 0; i < KIDS; ++i) {
        kid_ids[i] = fork();
        if (kid_ids[i] == 0) {
            close(pipefd[i * 2]);
            int b = rand() % 100;
            int f = b + (rand() % 10 + 1);
            write(pipefd[i * 2 + 1], &b, sizeof(int));
            write(pipefd[i * 2 + 1], &f, sizeof(int));
            close(pipefd[i * 2 + 1]);
            exit(0);
        } else if (kid_ids[i] < 0) {
            cerr << "Kid creation failed!\n";
            return 1;
        }
        close(pipefd[i * 2 + 1]);
    }

    for (int i = 0; i < KIDS; ++i) {
        int b, f;
        read(pipefd[i * 2], &b, sizeof(int));
        read(pipefd[i * 2], &f, sizeof(int));
        start_nums[i] = b;  
        finish[i] = f;
        work_time[i] = f - b;
        close(pipefd[i * 2]);
    }

    for (int i = 0; i < KIDS; ++i) {
        waitpid(kid_ids[i], nullptr, 0);
        cout << "Kid ID: " << kid_ids[i] 
             << ", Begin: " << start_nums[i] 
             << ", Finish: " << finish[i]
             << ", Work Time: " << work_time[i] << " sec\n";
    }

      int busiest = 0;
    for (int i = 1; i < KIDS; ++i) {
        if (work_time[i] > work_time[busiest]) {
            busiest = i;
        }
    }
    cout << "Busiest Kid: ID " << kid_ids[busiest] 
         << " with " << work_time[busiest] << " sec\n";

    return 0;
}
