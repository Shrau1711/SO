#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resources: ";
    cin >> m;

    vector<int> available(m);
    cout << "Enter available instances of each resource:\n";
    for (int i = 0; i < m; i++)
        cin >> available[i];

    vector<vector<int>> alloc(n, vector<int>(m));
    vector<vector<int>> max(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));

    cout << "\nEnter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> alloc[i][j];

    cout << "\nEnter Max Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> max[i][j];

    // Calculate Need Matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Detecting Deadlock:
    vector<bool> finish(n, false);
    vector<int> work = available;
    int count = 0;

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canRun = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canRun = false;
                        break;
                    }
                }
                if (canRun) {
                    // Process can finish — release its Allocation
                    for (int j = 0; j < m; j++)
                        work[j] += alloc[i][j];

                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) break;
    }

    // If not all processes can finish, we have a deadlock
    bool deadlock = false;
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            deadlock = true;
            cout << "Deadlock detected! Process " << i << " is in deadlock." << endl;
        }
    }

    if (!deadlock)
        cout << "No deadlock detected.\n";

    return 0;
}
