#include<iostream>
using namespace std;

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) { // for each process
        for (int j = 0; j < m; j++) { // check blocks
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    cout << "\nFirst Fit Allocation:\n";
    int totalFragment = 0;
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            cout << "Process " << processSize[i] << " KB --> Block " 
                 << allocation[i]+1 << " (Remaining: " << blockSize[allocation[i]] << " KB)\n";
        else
            cout << "Process " << processSize[i] << " KB --> Not Allocated\n";
    }
    for (int i = 0; i < m; i++) totalFragment += blockSize[i];
    cout << "Total External Fragmentation: " << totalFragment << " KB\n";
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    cout << "\nBest Fit Allocation:\n";
    int totalFragment = 0;
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            cout << "Process " << processSize[i] << " KB --> Block " 
                 << allocation[i]+1 << " (Remaining: " << blockSize[allocation[i]] << " KB)\n";
        else
            cout << "Process " << processSize[i] << " KB --> Not Allocated\n";
    }
    for (int i = 0; i < m; i++) totalFragment += blockSize[i];
    cout << "Total External Fragmentation: " << totalFragment << " KB\n";
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    cout << "\nWorst Fit Allocation:\n";
    int totalFragment = 0;
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            cout << "Process " << processSize[i] << " KB --> Block " 
                 << allocation[i]+1 << " (Remaining: " << blockSize[allocation[i]] << " KB)\n";
        else
            cout << "Process " << processSize[i] << " KB --> Not Allocated\n";
    }
    for (int i = 0; i < m; i++) totalFragment += blockSize[i];
    cout << "Total External Fragmentation: " << totalFragment << " KB\n";
}

int main() {
    int m, n;
    cout << "Enter number of memory blocks: ";
    cin >> m;
    int blockSize[m], originalBlockSize[m];
    cout << "Enter sizes of memory blocks:\n";
    for (int i = 0; i < m; i++) {
        cin >> blockSize[i];
        originalBlockSize[i] = blockSize[i];
    }

    cout << "Enter number of processes: ";
    cin >> n;
    int processSize[n];
    cout << "Enter sizes of processes:\n";
    for (int i = 0; i < n; i++)
        cin >> processSize[i];

    // Call First Fit
    firstFit(blockSize, m, processSize, n);

    // Reset block sizes for next run
    for (int i = 0; i < m; i++) blockSize[i] = originalBlockSize[i];

    // Call Best Fit
    bestFit(blockSize, m, processSize, n);

    // Reset block sizes again
    for (int i = 0; i < m; i++) blockSize[i] = originalBlockSize[i];

    // Call Worst Fit
    worstFit(blockSize, m, processSize, n);

    return 0;
}
