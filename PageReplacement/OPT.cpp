#include <iostream>
#include <vector>
using namespace std;

int predict(vector<int> &memory, vector<int> &ref, int index) {
    int farthest = index, pos = -1;
    for (int i = 0; i < memory.size(); i++) {
        int j;
        for (j = index; j < ref.size(); j++) {
            if (memory[i] == ref[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == ref.size()) // never used again
            return i;
    }
    return (pos == -1) ? 0 : pos;
}

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
            if (memory.size() < frames) {
                memory.push_back(page);
            } else {
                int pos = predict(memory, referenceString, i + 1);
                memory[pos] = page;
            }
            faults++;
            cout << "Page " << page << " caused a page fault.\n";
        } else {
            cout << "Page " << page << " — No page fault.\n";
        }
    }

    cout << "Total page faults = " << faults << endl;
    return 0;
}
