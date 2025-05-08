#include <iostream>
using namespace std;

int main() {
    int numSegments, segmentNumber, offset;

    cout << "Enter number of segments: ";
    cin >> numSegments;

    int base[numSegments], limit[numSegments];

    cout << "Enter base and limit for each segment:\n";
    for (int i = 0; i < numSegments; i++) {
        cout << "Segment " << i << " Base: ";
        cin >> base[i];
        cout << "Segment " << i << " Limit: ";
        cin >> limit[i];
    }

    cout << "Enter Segment Number: ";
    cin >> segmentNumber;
    cout << "Enter Offset: ";
    cin >> offset;

    if (segmentNumber >= numSegments) {
        cout << "Invalid segment number!\n";
        return 0;
    }

    if (offset > limit[segmentNumber]) {
        cout << "Segmentation Fault: Offset exceeds limit.\n";
        return 0;
    }

    int physicalAddress = base[segmentNumber] + offset;

    cout << "Base Address: " << base[segmentNumber] << endl;
    cout << "Limit: " << limit[segmentNumber] << endl;
    cout << "Physical Address: " << physicalAddress << endl;

    return 0;
}
