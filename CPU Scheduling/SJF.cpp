#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    bool isCompleted;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for(int i = 0; i < n; i++) {
        processes[i].pid = i+1;
        cout << "Enter Arrival Time for Process P" << i+1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter Burst Time for Process P" << i+1 << ": ";
        cin >> processes[i].burstTime;
        processes[i].isCompleted = false;
    }

    int completed = 0, currentTime = 0;
    float totalTAT = 0, totalWT = 0;

    cout << "\nGantt Chart:\n";

    vector<int> timeline; // for timestamps
    timeline.push_back(0); // start at 0

    while(completed != n) {
        int idx = -1;
        int minBT = 9999;

        // Find process with minimum burst time among arrived and incomplete ones
        for(int i = 0; i < n; i++) {
            if(processes[i].arrivalTime <= currentTime && !processes[i].isCompleted) {
                if(processes[i].burstTime < minBT) {
                    minBT = processes[i].burstTime;
                    idx = i;
                }
                else if(processes[i].burstTime == minBT) {
                    // If burst times are equal, go for earlier arrival time
                    if(processes[i].arrivalTime < processes[idx].arrivalTime)
                        idx = i;
                }
            }
        }

        if(idx != -1) {
            cout << "| P" << processes[idx].pid << " ";

            currentTime = max(currentTime, processes[idx].arrivalTime); // if idle, jump to arrival time
            processes[idx].completionTime = currentTime + processes[idx].burstTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;

            totalTAT += processes[idx].turnaroundTime;
            totalWT += processes[idx].waitingTime;

            currentTime = processes[idx].completionTime;
            processes[idx].isCompleted = true;
            completed++;

            timeline.push_back(currentTime);
        }
        else {
            // If no process has arrived, just move time ahead
            currentTime++;
            timeline.push_back(currentTime);
        }
    }
    cout << "|\n";

    // Print timeline below Gantt Chart
    cout << timeline[0];
    for(size_t i = 1; i < timeline.size(); i++) {
        cout << setw(5) << timeline[i];
    }
    cout << endl;

    // Display table
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for(int i = 0; i < n; i++) {
        cout << "P" << processes[i].pid << "\t"
             << processes[i].arrivalTime << "\t"
             << processes[i].burstTime << "\t"
             << processes[i].completionTime << "\t"
             << processes[i].turnaroundTime << "\t"
             << processes[i].waitingTime << endl;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time: " << totalTAT/n;
    cout << "\nAverage Waiting Time: " << totalWT/n << endl;

    return 0;
}
