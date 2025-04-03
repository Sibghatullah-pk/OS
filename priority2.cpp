#include <iostream>
using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int remaining_time; // To track remaining burst time
    bool completed;
    int last_executed; // To track when the process was last executed (for waiting time calculation)
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
        processes[i].remaining_time = processes[i].burst_time; // Initialize remaining time
        processes[i].completed = false;
        processes[i].waiting_time = 0;
        processes[i].last_executed = -1; // Not executed yet
    }

    int current_time = 0, completed_count = 0;
    float total_waiting_time = 0;
    int current_process = -1; // Track the currently executing process

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
            // No process is available, move time forward
            current_time++;
            continue;
        }

        // If a new process with higher priority arrives, preempt the current process
        if (current_process != selected_process && current_process != -1) {
            cout << "Time " << current_time << ": Process " << processes[current_process].pid << " preempted\n";
        }

        current_process = selected_process;
        Process &p = processes[selected_process];

        // If this is the first time the process is being executed, set last_executed
        if (p.last_executed == -1) {
            p.last_executed = current_time;
        }

        // Execute the process for 1 time unit
        p.remaining_time--;
        cout << "Time " << current_time << ": Process " << p.pid << " executing (Remaining Time: " << p.remaining_time << ")\n";

        // If process is completed
        if (p.remaining_time == 0) {
            p.turnaround_time = current_time + 1 - p.arrival_time;
            // Waiting time = Turnaround time - Burst time
            p.waiting_time = p.turnaround_time - p.burst_time;
            p.completed = true;
            completed_count++;
            total_waiting_time += p.waiting_time;
            cout << "Time " << current_time + 1 << ": Process " << p.pid << " completed\n";
            current_process = -1; // Reset current process
        }

        current_time++;
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
