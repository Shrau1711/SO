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

    vector<vector<int>> max(n, vector<int>(m));
    vector<vector<int>> alloc(n, vector<int>(m));
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

    // Display Need Matrix
    cout << "\nNeed Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << need[i][j] << " ";
        cout << endl;
    }

    // Safety Algorithm
    vector<bool> finish(n, false);
    vector<int> work = available;
    vector<int> safeSeq;

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
                    // Process can run — release its Allocation
                    for (int j = 0; j < m; j++)
                        work[j] += alloc[i][j];

                    safeSeq.push_back(i);
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) break;
    }

    // Output result
    if (safeSeq.size() == n) {
        cout << "\nSystem is in a safe state.\nSafe Sequence: ";
        for (int i = 0; i < n; i++)
            cout << "P" << safeSeq[i] << (i == n-1 ? "" : " -> ");
        cout << endl;
    } else {
        cout << "\nSystem is NOT in a safe state. Deadlock possible.\n";
    }

    return 0;
}
