#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numberCount, selectionCount;
    cin >> numberCount >> selectionCount;
    vector<vector<int>> selections;
    for (int mask = 0; mask < (1 << numberCount); ++mask) {
        vector<int> selection;
        for (int value = 1; value <= numberCount; ++value) {
            if (mask & (1 << (value - 1))) {
                selection.push_back(value);
            }
        }
        if (static_cast<int>(selection.size()) == selectionCount) {
            selections.push_back(selection);
        }
    }

    sort(selections.begin(), selections.end());
    for (const vector<int>& selection : selections) {
        for (int value : selection) {
            cout << value << ' ';
        }
        cout << '\n';
    }
    return 0;
}
