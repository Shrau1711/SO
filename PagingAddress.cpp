#include <iostream>
using namespace std;

int main() {
    int pageSize, logicalAddress, numPages;
    
    cout << "Enter page size (bytes): ";
    cin >> pageSize;

    cout << "Enter number of pages: ";
    cin >> numPages;

    int pageTable[numPages];
    cout << "Enter frame number for each page:\n";
    for (int i = 0; i < numPages; i++) {
        cout << "Page " << i << ": ";
        cin >> pageTable[i];
    }

    cout << "Enter logical address: ";
    cin >> logicalAddress;

    int pageNumber = logicalAddress / pageSize;
    int offset = logicalAddress % pageSize;

    if (pageNumber >= numPages) {
        cout << "Invalid logical address! Page number out of range.\n";
        return 0;
    }

    int frameNumber = pageTable[pageNumber];
    int physicalAddress = (frameNumber * pageSize) + offset;

    cout << "Page Number: " << pageNumber << endl;
    cout << "Offset: " << offset << endl;
    cout << "Frame Number: " << frameNumber << endl;
    cout << "Physical Address: " << physicalAddress << endl;

    return 0;
}
