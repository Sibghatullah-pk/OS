#include <iostream>
using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    bool completed;
};

int main() {
    int n;
    cout << "Kitne processes hain? ";
    cin >> n;

    Process processes[n];
    
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Process " << processes[i].pid << " ka arrival time, burst time, aur priority daalo: ";
        cin >> processes[i].arrival_time >> processes[i].burst_time >> processes[i].priority;
        processes[i].completed = false;
    }

    int current_time = 0, completed_count = 0;
    float total_waiting_time = 0;

    while (completed_count < n) {
        int highest_priority = -1, selected_process = -1;

        // Find the highest priority process available at current time
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrival_time <= current_time) {
                if (highest_priority == -1 || processes[i].priority > highest_priority) { 
                    highest_priority = processes[i].priority;
                    selected_process = i;
                }
            }
        }

        if (selected_process == -1) {
            current_time++; // If no process is available, move time forward
            continue;
        }

        // Execute the selected process
        Process &p = processes[selected_process];
        p.waiting_time = current_time - p.arrival_time;
        current_time += p.burst_time;
        p.turnaround_time = current_time - p.arrival_time;
        p.completed = true;

        total_waiting_time += p.waiting_time;
        completed_count++;
    }

    // Output results
    cout << "\nProcess ID | Priority | Waiting Time | Turnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << "   " << processes[i].pid << "\t\t"
             << processes[i].priority << "\t\t"
             << processes[i].waiting_time << "\t\t"
             << processes[i].turnaround_time << endl;
    }

    cout << "Average Waiting Time: " << total_waiting_time / n << endl;

    return 0;
}
