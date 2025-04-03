#include <iostream>
using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
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
        processes[i].remaining_time = processes[i].burst_time;
    }

    int current_time = 0, completed_count = 0;
    float total_waiting_time = 0;

    while (completed_count < n) {
        int shortest_time = 99999, selected_process = -1;

        // Find the process with the shortest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0 && processes[i].arrival_time <= current_time) {
                if (processes[i].remaining_time < shortest_time) {
                    shortest_time = processes[i].remaining_time;
                    selected_process = i;
                }
            }
        }

        if (selected_process == -1) {
            // If no process is available, jump to the next arrival time
            int next_arrival = 99999;
            for (int i = 0; i < n; i++) {
                if (processes[i].remaining_time > 0 && processes[i].arrival_time > current_time) {
                    next_arrival = min(next_arrival, processes[i].arrival_time);
                }
            }
            current_time = next_arrival;
            continue;
        }

        // Execute the selected process for 1 unit of time
        processes[selected_process].remaining_time--;
        current_time++;

        // If the process is completed
        if (processes[selected_process].remaining_time == 0) {
            completed_count++;
            processes[selected_process].turnaround_time = current_time - processes[selected_process].arrival_time;
            processes[selected_process].waiting_time = processes[selected_process].turnaround_time - processes[selected_process].burst_time;
            total_waiting_time += processes[selected_process].waiting_time;
        }
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
