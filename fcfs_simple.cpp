#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

// Comparator function for sorting by arrival time
bool arrival(Process a, Process b) {
    return a.arrival_time < b.arrival_time;
}

int main() {
    int n;
    cout << "Kitne processes hain? ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Process " << processes[i].pid << " ka arrival time aur burst time daalo: ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
    }

    // Arrival time ke basis pe sort karo
    sort(processes.begin(), processes.end(), arrival);

    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        processes[i].waiting_time = current_time - processes[i].arrival_time;
        current_time += processes[i].burst_time;
        processes[i].turnaround_time = current_time - processes[i].arrival_time;
    }

    float total_waiting_time = 0;
    for (auto p : processes) {
        total_waiting_time += p.waiting_time;
        cout << "Process " << p.pid << ": Waiting Time = " << p.waiting_time << ", Turnaround Time = " << p.turnaround_time << endl;
    }

    cout << "Average Waiting Time: " << total_waiting_time / n << endl;

    return 0;
}


