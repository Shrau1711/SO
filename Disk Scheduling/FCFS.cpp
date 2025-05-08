#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

void FCFS(vector<int> requests, int head) {
    int totalSeek = 0;

    cout << "\n--- FCFS Disk Scheduling ---\n";
    cout << "Next Track\tTracks Traversed\n";

    for (int track : requests) {
        int dist = abs(track - head);
        cout << setw(10) << track << "\t" << setw(10) << dist << endl;
        totalSeek += dist;
        head = track;
    }

    double avgSeek = (double)totalSeek / requests.size();
    cout << "Total Tracks Traversed: " << totalSeek << endl;
    cout << "Average Seek Time: " << avgSeek << endl;
}

int main() {
    int head, n;
    cout << "Enter current head position: ";
    cin >> head;
    cout << "Enter number of requests: ";
    cin >> n;

    vector<int> requests(n);
    cout << "Enter request queue (track numbers): ";
    for (int i = 0; i < n; i++)
        cin >> requests[i];

    FCFS(requests, head);

    return 0;
}
