#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class FenwickMaximum {
public:
    explicit FenwickMaximum(int size) : tree(size + 1) {}

    int query(int index) const {
        int result = 0;
        while (index > 0) {
            result = max(result, tree[index]);
            index -= index & -index;
        }
        return result;
    }

    void update(int index, int value) {
        while (index < static_cast<int>(tree.size())) {
            tree[index] = max(tree[index], value);
            index += index & -index;
        }
    }

private:
    vector<int> tree;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int, int>> meetings(n);
    vector<int> coordinates;
    coordinates.reserve(2 * n);
    for (auto &[end, start] : meetings) {
        cin >> start >> end;
        coordinates.push_back(start);
        coordinates.push_back(end);
    }
    sort(meetings.begin(), meetings.end());
    sort(coordinates.begin(), coordinates.end());
    coordinates.erase(unique(coordinates.begin(), coordinates.end()), coordinates.end());

    FenwickMaximum best(static_cast<int>(coordinates.size()));
    int answer = 0;
    for (const auto &[end, start] : meetings) {
        const int startIndex = upper_bound(coordinates.begin(), coordinates.end(), start) - coordinates.begin();
        const int endIndex = lower_bound(coordinates.begin(), coordinates.end(), end) - coordinates.begin() + 1;
        const int count = best.query(startIndex) + 1;
        best.update(endIndex, count);
        answer = max(answer, count);
    }

    cout << answer << '\n';
    return 0;
}
