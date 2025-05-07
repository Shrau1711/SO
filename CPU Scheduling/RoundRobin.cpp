#include <iostream>
#include <vector>
#include <queue>
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
};

int main() {
    int n, timeQuantum;
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
    }

    cout << "Enter Time Quantum: ";
    cin >> timeQuantum;

    queue<int> readyQueue;
    int currentTime = 0, completed = 0;
    float totalTAT = 0, totalWT = 0;
    vector<bool> inQueue(n, false);

    cout << "\nGantt Chart:\n";
    cout << currentTime;

    while(completed != n) {
        // Add processes that have arrived to the queue
        for(int i = 0; i < n; i++) {
            if(processes[i].arrivalTime <= currentTime && !inQueue[i] && processes[i].remainingTime > 0) {
                readyQueue.push(i);
                inQueue[i] = true;
            }
        }

        if(!readyQueue.empty()) {
            int idx = readyQueue.front();
            readyQueue.pop();

            cout << " | P" << processes[idx].pid << " " << currentTime;

            int execTime = min(timeQuantum, processes[idx].remainingTime);
            currentTime += execTime;
            processes[idx].remainingTime -= execTime;

            // Add new arrivals while process is executing
            for(int i = 0; i < n; i++) {
                if(processes[i].arrivalTime > (currentTime - execTime) && processes[i].arrivalTime <= currentTime && !inQueue[i] && processes[i].remainingTime > 0) {
                    readyQueue.push(i);
                    inQueue[i] = true;
                }
            }

            if(processes[idx].remainingTime > 0) {
                readyQueue.push(idx);
            } else {
                processes[idx].completionTime = currentTime;
                processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;

                totalTAT += processes[idx].turnaroundTime;
                totalWT += processes[idx].waitingTime;
                completed++;
            }
        } else {
            currentTime++; // Idle time
        }
    }

    cout << " |\n" << currentTime << endl;

    // Display Table
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
