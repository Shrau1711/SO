#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

void CSCAN(vector<int> requests, int head, int diskSize) {
    int totalSeek = 0;

    vector<int> left, right;

    // Split requests into those greater and less than head
    for (int track : requests) {
        if (track >= head)
            right.push_back(track);
        else
            left.push_back(track);
    }

    sort(right.begin(), right.end());
    sort(left.begin(), left.end());

    cout << "\n--- C-SCAN Disk Scheduling ---\n";
    cout << "Next Track\tTracks Traversed\n";

    // Move towards higher track numbers
    for (int track : right) {
        int dist = abs(track - head);
        cout << setw(10) << track << "\t" << setw(10) << dist << endl;
        totalSeek += dist;
        head = track;
    }

    // Jump from last track to end, then to start (if left queue not empty)
    if (!left.empty()) {
        int distToEnd = (diskSize - 1) - head;
        int distToStart = (diskSize - 1);
        totalSeek += distToEnd + distToStart;
        head = 0;
    }

    // Service remaining requests
    for (int track : left) {
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
    int diskSize, head, n;
    cout << "Enter total number of tracks in disk: ";
    cin >> diskSize;
    cout << "Enter current head position: ";
    cin >> head;
    cout << "Enter number of requests: ";
    cin >> n;

    vector<int> requests(n);
    cout << "Enter request queue (track numbers): ";
    for (int i = 0; i < n; i++)
        cin >> requests[i];

    CSCAN(requests, head, diskSize);

    return 0;
}
