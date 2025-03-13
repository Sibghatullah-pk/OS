#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

const int MAX = 5;  // Total resources
const int KIDS = 3; // Number of child processes

int resources = MAX;  // Start with all resources

void give_resource(int need) {
    if (resources >= need) {
        resources = resources - need;
        cout << "Child (ID: " << getpid() << ") got " << need 
             << " resources. Left: " << resources << endl;
    } else {
        cout << "Child (ID: " << getpid() << ") can’t get " << need 
             << " resources. Not enough: " << resources << endl;
    }
}

void take_resource(int need) {
    resources = resources + need;
    cout << "Child (ID: " << getpid() << ") gave back " << need 
         << " resources. Now: " << resources << endl;
}

int main() {
    int pids[KIDS];
    int status;

    // Make child processes
    for (int i = 0; i < KIDS; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {  // Child
            int need = i + 1;  // Need 1, 2, or 3 resources
            give_resource(need);
            sleep(2);  // Wait 2 seconds (like using resources)
            take_resource(need);
            exit(0);  // Child done
        } else if (pids[i] < 0) {
            cout << "Can’t make child" << endl;
            exit(1);
        }
    }

    // Parent waits for kids and tracks resources
    cout << "Parent (ID: " << getpid() << ") tracking resources. Start with: " 
         << resources << endl;
    for (int i = 0; i < KIDS; i++) {
        waitpid(pids[i], &status, 0);  // Wait for each child
        if (WIFEXITED(status)) {
            cout << "Parent: Child " << i + 1 << " (ID: " << pids[i] 
                 << ") done, resources updated" << endl;
        }
    }
    cout << "Parent: All resources back. Now: " << resources << endl;
    return 0;
}
