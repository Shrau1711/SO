#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

// Node to represent each memory block
struct Node {
    int size;
    bool isAllocated;
    int processId;
    Node* left;
    Node* right;

    Node(int s) {
        size = s;
        isAllocated = false;
        processId = -1;
        left = right = nullptr;
    }
};

// Function to display the tree
void displayTree(Node* root, int level = 0) {
    if (root == nullptr) return;
    
    displayTree(root->right, level + 1);
    
    cout << setw(4 * level) << " ";
    cout << "[Size: " << root->size;
    if (root->isAllocated)
        cout << " | P" << root->processId << "]";
    else
        cout << " | Free]";
    cout << endl;

    displayTree(root->left, level + 1);
}

// Allocate memory using Buddy System
bool allocate(Node* &root, int processSize, int processId, int &internalFragmentation) {
    if (root->isAllocated) return false;

    // If process can exactly fit
    if (root->size == processSize) {
        root->isAllocated = true;
        root->processId = processId;
        return true;
    }

    // If block is too small
    if (root->size < processSize) return false;

    // Split the block into two buddies
    if (root->left == nullptr && root->right == nullptr) {
        root->left = new Node(root->size / 2);
        root->right = new Node(root->size / 2);
    }

    // Try allocating in left buddy
    if (allocate(root->left, processSize, processId, internalFragmentation))
        return true;

    // Try allocating in right buddy
    if (allocate(root->right, processSize, processId, internalFragmentation))
        return true;

    return false;
}

int main() {
    int totalMemory, numProcesses;
    cout << "Enter total memory size (power of 2): ";
    cin >> totalMemory;

    cout << "Enter number of processes: ";
    cin >> numProcesses;

    vector<int> processSizes(numProcesses);
    for (int i = 0; i < numProcesses; i++) {
        cout << "Enter size of Process " << i + 1 << ": ";
        cin >> processSizes[i];
    }

    Node* root = new Node(totalMemory);
    int internalFragmentation = 0;

    // Allocate processes
    for (int i = 0; i < numProcesses; i++) {
        // Find nearest power of 2
        int blockSize = pow(2, ceil(log2(processSizes[i])));
        if (blockSize > totalMemory) {
            cout << "Process " << i+1 << " cannot be allocated. Not enough memory!" << endl;
            continue;
        }

        if (!allocate(root, blockSize, i + 1, internalFragmentation)) {
            cout << "Process " << i+1 << " cannot be allocated. No suitable block available!" << endl;
        } else {
            internalFragmentation += (blockSize - processSizes[i]);
        }
    }

    cout << "\nFinal Memory Tree:\n";
    displayTree(root);

    cout << "\nTotal Internal Fragmentation: " << internalFragmentation << " KB" << endl;

    return 0;
}
