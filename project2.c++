#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Process {
    int pid;         // Process ID
    int arrivalTime; // Arrival time of the process
    int burstTime;   // Burst time (time needed to complete)
    int waitingTime; // Time a process spends waiting
    int turnaroundTime; // Time from arrival to completion
    int priority;    // Used for Priority Scheduling
};

// Compare processes by burst time (for SJF)
bool compareByBurstTime(Process a, Process b) {
    return a.burstTime < b.burstTime;
}

// Compare processes by arrival time (for FCFS)
bool compareByArrivalTime(Process a, Process b) {
    return a.arrivalTime < b.arrivalTime;
}

// Compare processes by priority (for Priority Scheduling)
bool compareByPriority(Process a, Process b) {
    return a.priority > b.priority; // Higher priority comes first
}

// FCFS Scheduling Algorithm
void FCFS(vector<Process>& processes) {
    int currentTime = 0;
    for (auto &p : processes) {
        if (currentTime < p.arrivalTime)
            currentTime = p.arrivalTime; // If no process arrived, wait
        p.waitingTime = currentTime - p.arrivalTime;
        currentTime += p.burstTime;
        p.turnaroundTime = p.waitingTime + p.burstTime;
    }
}

// SJF Scheduling Algorithm (Non-preemptive)
void SJF(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compareByBurstTime); // Sort by burst time
    FCFS(processes); // SJF can be done by FCFS after sorting by burst time
}

// Round Robin Scheduling Algorithm
void RoundRobin(vector<Process>& processes, int quantum) {
    int currentTime = 0;
    int remainingProcesses = processes.size();
    vector<int> remainingBurstTime(processes.size());

    for (int i = 0; i < processes.size(); i++) {
        remainingBurstTime[i] = processes[i].burstTime; // Store burst time
    }

    while (remainingProcesses > 0) {
        for (int i = 0; i < processes.size(); i++) {
            if (remainingBurstTime[i] > 0) {
                int timeSlice = min(quantum, remainingBurstTime[i]);
                processes[i].waitingTime += currentTime - processes[i].arrivalTime;
                currentTime += timeSlice;
                remainingBurstTime[i] -= timeSlice;

                if (remainingBurstTime[i] == 0) {
                    processes[i].turnaroundTime = currentTime - processes[i].arrivalTime;
                    remainingProcesses--;
                }
            }
        }
    }
}

// Priority Scheduling Algorithm
void PriorityScheduling(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compareByPriority); // Sort by priority
    FCFS(processes); // Use FCFS after sorting by priority
}

// Display results for any algorithm
void displayResults(const vector<Process>& processes) {
    cout << "\nPID\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n";
    for (auto p : processes) {
        cout << p.pid << "\t" << p.arrivalTime << "\t" 
             << p.burstTime << "\t" << (p.priority ? to_string(p.priority) : "N/A") 
             << "\t\t" << p.waitingTime << "\t" 
             << p.turnaroundTime << "\n";
    }

    // Display Gantt chart
    cout << "\nGantt Chart:\n";
    int time = 0;
    for (auto p : processes) {
        cout << "| P" << p.pid << " ";
    }
    cout << "|\n";
    for (auto p : processes) {
        cout << time << "\t";
        time += p.burstTime;
    }
    cout << time << endl;
}

int main() {
    int n, choice;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter arrival time of process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time of process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        cout << "Enter priority of process " << i + 1 << " (higher value means higher priority): ";
        cin >> processes[i].priority;
    }

    // Error handling for invalid inputs
    if (n <= 0) {
        cout << "Error: Number of processes must be greater than 0!" << endl;
        return 1;
    }

    cout << "Choose Scheduling Algorithm: \n1. FCFS \n2. SJF \n3. Round Robin \n4. Priority Scheduling\n";
    cout << "Enter choice: ";
    cin >> choice;

    int quantum = 0;
    if (choice == 3) {
        cout << "Enter time quantum for Round Robin: ";
        cin >> quantum;
        if (quantum <= 0) {
            cout << "Error: Time quantum must be greater than 0!" << endl;
            return 1;
        }
    }

    // Apply chosen scheduling algorithm
    switch (choice) {
        case 1: FCFS(processes); break;
        case 2: SJF(processes); break;
        case 3: RoundRobin(processes, quantum); break;
        case 4: PriorityScheduling(processes); break;
        default: 
            cout << "Invalid choice!" << endl;
            return 1;
    }

    displayResults(processes);

    return 0;
}

