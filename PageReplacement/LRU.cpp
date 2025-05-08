#include <iostream>
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

    vector<int> memory;

    for (int i = 0; i < pages; i++) {
        page = referenceString[i];
        auto it = find(memory.begin(), memory.end(), page);

        if (it == memory.end()) {
            if (memory.size() == frames) {
                memory.erase(memory.begin()); // remove least recently used
            }
            faults++;
            cout << "Page " << page << " caused a page fault.\n";
        } else {
            memory.erase(it);
            cout << "Page " << page << " — No page fault.\n";
        }

        memory.push_back(page); // most recently used at end
    }

    cout << "Total page faults = " << faults << endl;
    return 0;
}
