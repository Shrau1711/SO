#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    int pid; // Process ID
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

// Function to sort processes by arrival time
bool compareArrival(Process a, Process b) {
    return a.arrivalTime < b.arrivalTime;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input process details
    for(int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter arrival time for Process " << processes[i].pid << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for Process " << processes[i].pid << ": ";
        cin >> processes[i].burstTime;
    }

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), compareArrival);

    int currentTime = 0;
    float totalTurnaroundTime = 0;
    float totalWaitingTime = 0;

    cout << "\nGantt Chart:\n";
    for(int i = 0; i < n; i++) {
        if(currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }
        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

        totalTurnaroundTime += processes[i].turnaroundTime;
        totalWaitingTime += processes[i].waitingTime;

        cout << "| P" << processes[i].pid << " ";
        currentTime = processes[i].completionTime;
    }
    cout << "|\n";

    // Display process details
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for(int i = 0; i < n; i++) {
        cout << "P" << processes[i].pid << "\t"
             << processes[i].arrivalTime << "\t"
             << processes[i].burstTime << "\t"
             << processes[i].completionTime << "\t"
             << processes[i].turnaroundTime << "\t"
             << processes[i].waitingTime << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time: " << totalTurnaroundTime / n;
    cout << "\nAverage Waiting Time: " << totalWaitingTime / n << "\n";

    return 0;
}
