#include <iostream>
using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    bool completed; // To track completed processes
};

int main() {
    int n;
    cout << "Kitne processes hain? ";
    cin >> n;

    Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Process " << processes[i].pid << " ka arrival time aur burst time daalo: ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
        processes[i].completed = false;
    }

    int current_time = 0, completed_count = 0;
    float total_waiting_time = 0;

    while (completed_count < n) {
        int shortest_index = -1;
        int min_burst_time = 99999; // Large number to find the minimum

        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrival_time <= current_time) {
                if (processes[i].burst_time < min_burst_time) {
                    min_burst_time = processes[i].burst_time;
                    shortest_index = i;
                }
            }
        }

        if (shortest_index == -1) {
            // No process has arrived yet, so move time forward
            current_time++;
            continue;
        }

        // Process selected
        processes[shortest_index].waiting_time = current_time - processes[shortest_index].arrival_time;
        current_time += processes[shortest_index].burst_time;
        processes[shortest_index].turnaround_time = current_time - processes[shortest_index].arrival_time;
        processes[shortest_index].completed = true;
        total_waiting_time += processes[shortest_index].waiting_time;

        completed_count++;
    }

    // Output results
    cout << "\nProcess ID | Waiting Time | Turnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << "   " << processes[i].pid << "\t\t"
             << processes[i].waiting_time << "\t\t"
             << processes[i].turnaround_time << endl;
    }

    cout << "Average Waiting Time: " << total_waiting_time / n << endl;

    return 0;
}
