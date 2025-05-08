#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

void SSTF(vector<int> requests, int head) {
    int totalSeek = 0;
    int n = requests.size();
    vector<bool> visited(n, false);

    cout << "\n--- SSTF Disk Scheduling ---\n";
    cout << "Next Track\tTracks Traversed\n";

    for (int count = 0; count < n; count++) {
        int minDist = INT_MAX;
        int index = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int dist = abs(requests[i] - head);
                if (dist < minDist) {
                    minDist = dist;
                    index = i;
                }
            }
        }

        // Service the closest track
        cout << setw(10) << requests[index] << "\t" << setw(10) << minDist << endl;
        totalSeek += minDist;
        head = requests[index];
        visited[index] = true;
    }

    double avgSeek = (double)totalSeek / n;
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

    SSTF(requests, head);

    return 0;
}
