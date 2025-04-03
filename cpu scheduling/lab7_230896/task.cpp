#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unistd.h>
using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};

float priorityScheduling(vector<Process> processes) {
    int n = processes.size();
    vector<Process> schedule;
    int current_time = 0;
    vector<bool> completed(n, false);
    int completed_count = 0;

    while (completed_count < n) {
        int highest_priority = -1;
        int selected_process = -1;

        for (int i = 0; i < n; i++) {
            if (!completed[i] && processes[i].arrival_time <= current_time) {
                if (highest_priority == -1 || processes[i].priority > highest_priority) {
                    highest_priority = processes[i].priority;
                    selected_process = i;
                }
            }
        }

        if (selected_process == -1) {
            current_time++;
            continue;
        }

        Process p = processes[selected_process];
        p.waiting_time = current_time - p.arrival_time;
        current_time += p.burst_time;
        p.turnaround_time = current_time - p.arrival_time;

        schedule.push_back(p);
        completed[selected_process] = true;
        completed_count++;
    }

    float total_waiting_time = 0;
    for (auto p : schedule) {
        total_waiting_time += p.waiting_time;
    }

    return total_waiting_time / n;
}

float srtfScheduling(vector<Process> processes) {
    int n = processes.size();
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrival_time < b.arrival_time;
    });

    int current_time = 0;
    int completed_count = 0;
    vector<bool> completed(n, false);

    while (completed_count < n) {
        int shortest_time = -1;
        int selected_process = -1;

        for (int i = 0; i < n; i++) {
            if (!completed[i] && processes[i].arrival_time <= current_time) {
                if (shortest_time == -1 || processes[i].remaining_time < shortest_time) {
                    shortest_time = processes[i].remaining_time;
                    selected_process = i;
                }
            }
        }

        if (selected_process == -1) {
            current_time++;
            continue;
        }

        processes[selected_process].remaining_time--;
        current_time++;

        if (processes[selected_process].remaining_time == 0) {
            completed[selected_process] = true;
            completed_count++;
            processes[selected_process].turnaround_time = current_time - processes[selected_process].arrival_time;
            processes[selected_process].waiting_time = processes[selected_process].turnaround_time - processes[selected_process].burst_time;
        }
    }

    float total_waiting_time = 0;
    for (auto p : processes) {
        total_waiting_time += p.waiting_time;
    }

    return total_waiting_time / n;
}

float mlfqScheduling(vector<Process> processes) {
    int n = processes.size();
    queue<Process> foreground_queue;
    queue<Process> background_queue;

    for (auto &p : processes) {
        if (p.priority >= 5) {
            foreground_queue.push(p);
        } else {
            background_queue.push(p);
        }
    }

    int current_time = 0;
    vector<bool> completed(n, false);
    int completed_count = 0;

    while (completed_count < n) {
        cout << "Time " << current_time << ": Foreground queue ko CPU milta hai 10 seconds ke liye\n";
        int foreground_time = 0;

        while (foreground_time < 10 && !foreground_queue.empty()) {
            vector<Process> temp;
            Process highest_priority = foreground_queue.front();
            foreground_queue.pop();

            while (!foreground_queue.empty()) {
                Process p = foreground_queue.front();
                foreground_queue.pop();
                if (p.priority > highest_priority.priority && p.arrival_time <= current_time) {
                    temp.push_back(highest_priority);
                    highest_priority = p;
                } else {
                    temp.push_back(p);
                }
            }

            for (auto p : temp) {
                foreground_queue.push(p);
            }

            if (highest_priority.arrival_time > current_time) {
                foreground_queue.push(highest_priority);
                current_time++;
                foreground_time++;
                continue;
            }

            highest_priority.remaining_time--;
            current_time++;
            foreground_time++;
            cout << "Time " << current_time << ": Process " << highest_priority.pid << " (Foreground) execute ho raha hai\n";

            if (highest_priority.remaining_time == 0) {
                highest_priority.completion_time = current_time;
                highest_priority.turnaround_time = current_time - highest_priority.arrival_time;
                highest_priority.waiting_time = highest_priority.turnaround_time - highest_priority.burst_time;
                for (int i = 0; i < n; i++) {
                    if (processes[i].pid == highest_priority.pid) {
                        processes[i] = highest_priority;
                        completed[i] = true;
                        completed_count++;
                        break;
                    }
                }
            } else {
                foreground_queue.push(highest_priority);
            }
        }

        cout << "Time " << current_time << ": Background queue ko CPU milta hai 3 seconds ke liye\n";
        int background_time = 0;

        while (background_time < 3 && !background_queue.empty()) {
            vector<Process> temp;
            Process shortest_time = background_queue.front();
            background_queue.pop();

            while (!background_queue.empty()) {
                Process p = background_queue.front();
                background_queue.pop();
                if (p.remaining_time < shortest_time.remaining_time && p.arrival_time <= current_time) {
                    temp.push_back(shortest_time);
                    shortest_time = p;
                } else {
                    temp.push_back(p);
                }
            }

            for (auto p : temp) {
                background_queue.push(p);
            }

            if (shortest_time.arrival_time > current_time) {
                background_queue.push(shortest_time);
                current_time++;
                background_time++;
                continue;
            }

            shortest_time.remaining_time--;
            current_time++;
            background_time++;
            cout << "Time " << current_time << ": Process " << shortest_time.pid << " (Background) execute ho raha hai\n";

            if (shortest_time.remaining_time == 0) {
                shortest_time.completion_time = current_time;
                shortest_time.turnaround_time = current_time - shortest_time.arrival_time;
                shortest_time.waiting_time = shortest_time.turnaround_time - shortest_time.burst_time;
                for (int i = 0; i < n; i++) {
                    if (processes[i].pid == shortest_time.pid) {
                        processes[i] = shortest_time;
                        completed[i] = true;
                        completed_count++;
                        break;
                    }
                }
            } else {
                background_queue.push(shortest_time);
            }
        }

        if (foreground_queue.empty() && background_queue.empty() && completed_count < n) {
            current_time++;
        }
    }

    float total_waiting_time = 0;
    for (auto p : processes) {
        total_waiting_time += p.waiting_time;
    }

    return total_waiting_time / n;
}

int main() {
    int n;
    cout << "Kitne processes hain? ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Process " << processes[i].pid << " ka arrival time, burst time, aur priority daalo: ";
        cin >> processes[i].arrival_time >> processes[i].burst_time >> processes[i].priority;
        processes[i].remaining_time = processes[i].burst_time;
    }

    vector<Process> processes_priority = processes;
    vector<Process> processes_srtf = processes;
    vector<Process> processes_mlfq = processes;

    float avg_waiting_priority = priorityScheduling(processes_priority);
    cout << "\nPriority-Based Scheduling ka Average Waiting Time: " << avg_waiting_priority << endl;

    float avg_waiting_srtf = srtfScheduling(processes_srtf);
    cout << "SRTF ka Average Waiting Time: " << avg_waiting_srtf << endl;

    float avg_waiting_mlfq = mlfqScheduling(processes_mlfq);
    cout << "MLFQ ka Average Waiting Time: " << avg_waiting_mlfq << endl;

    cout << "\nComparison:\n";
    cout << "Priority-Based: " << avg_waiting_priority << endl;
    cout << "SRTF: " << avg_waiting_srtf << endl;
    cout << "MLFQ: " << avg_waiting_mlfq << endl;

    return 0;
}
