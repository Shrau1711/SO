#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

void SCAN(vector<int> requests, int head, int diskSize, string direction) {
    int totalSeek = 0;
    vector<int> left, right;

    // Add end points depending on direction
    if (direction == "left")
        left.push_back(0);
    else if (direction == "right")
        right.push_back(diskSize - 1);

    // Split requests
    for (int track : requests) {
        if (track < head)
            left.push_back(track);
        else
            right.push_back(track);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    cout << "\n--- SCAN Disk Scheduling (" << direction << ") ---\n";
    cout << "Next Track\tTracks Traversed\n";

    if (direction == "left") {
        // Move towards 0
        for (int i = left.size() - 1; i >= 0; i--) {
            int dist = abs(head - left[i]);
            cout << setw(10) << left[i] << "\t" << setw(10) << dist << endl;
            totalSeek += dist;
            head = left[i];
        }
        // Move towards end
        for (int i = 0; i < right.size(); i++) {
            int dist = abs(head - right[i]);
            cout << setw(10) << right[i] << "\t" << setw(10) << dist << endl;
            totalSeek += dist;
            head = right[i];
        }
    } else if (direction == "right") {
        // Move towards end
        for (int i = 0; i < right.size(); i++) {
            int dist = abs(head - right[i]);
            cout << setw(10) << right[i] << "\t" << setw(10) << dist << endl;
            totalSeek += dist;
            head = right[i];
        }
        // Move towards 0
        for (int i = left.size() - 1; i >= 0; i--) {
            int dist = abs(head - left[i]);
            cout << setw(10) << left[i] << "\t" << setw(10) << dist << endl;
            totalSeek += dist;
            head = left[i];
        }
    }

    double avgSeek = (double)totalSeek / requests.size();
    cout << "Total Tracks Traversed: " << totalSeek << endl;
    cout << "Average Seek Time: " << avgSeek << endl;
}

int main() {
    int diskSize, head, n;
    string direction;
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

    cout << "Enter initial direction (left/right): ";
    cin >> direction;

    SCAN(requests, head, diskSize, direction);

    return 0;
}
