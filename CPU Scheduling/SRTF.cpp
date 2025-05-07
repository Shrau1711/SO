#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
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
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].isCompleted = false;
    }

    int completed = 0, currentTime = 0;
    float totalTAT = 0, totalWT = 0;
    int lastProcess = -1;

    cout << "\nGantt Chart:\n";
    cout << currentTime;

    while(completed != n) {
        int idx = -1;
        int minRT = 9999;

        // Find process with minimum remaining time
        for(int i = 0; i < n; i++) {
            if(processes[i].arrivalTime <= currentTime && !processes[i].isCompleted) {
                if(processes[i].remainingTime < minRT) {
                    minRT = processes[i].remainingTime;
                    idx = i;
                }
                else if(processes[i].remainingTime == minRT) {
                    // Tie-breaker by earlier arrival time
                    if(processes[i].arrivalTime < processes[idx].arrivalTime)
                        idx = i;
                }
            }
        }

        if(idx != -1) {
            if(lastProcess != idx) {
                cout << " | P" << processes[idx].pid << " " << currentTime;
                lastProcess = idx;
            }

            processes[idx].remainingTime--;
            currentTime++;

            if(processes[idx].remainingTime == 0) {
                processes[idx].completionTime = currentTime;
                processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;

                totalTAT += processes[idx].turnaroundTime;
                totalWT += processes[idx].waitingTime;

                processes[idx].isCompleted = true;
                completed++;
            }
        }
        else {
            // If no process has arrived, just idle
            currentTime++;
        }
    }

    cout << " |\n" << currentTime << endl;

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
