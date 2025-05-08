#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    int frames, pages, page, faults = 0;
    cout << "Enter number of frames: ";
    cin >> frames;
    cout << "Enter number of page references: ";
    cin >> pages;

    vector<int> referenceString(pages);
    cout << "Enter reference string: ";
    for (int i = 0; i < pages; i++)
        cin >> referenceString[i];

    queue<int> memory;
    vector<int> inMemory;

    for (int i = 0; i < pages; i++) {
        page = referenceString[i];
        bool found = false;

        for (int p : inMemory) {
            if (p == page) {
                found = true;
                break;
            }
        }

        if (!found) {
            if (inMemory.size() == frames) {
                inMemory.erase(inMemory.begin()); // remove oldest
            }
            inMemory.push_back(page);
            faults++;
            cout << "Page " << page << " caused a page fault.\n";
        } else {
            cout << "Page " << page << " — No page fault.\n";
        }
    }

    cout << "Total page faults = " << faults << endl;
    return 0;
}
