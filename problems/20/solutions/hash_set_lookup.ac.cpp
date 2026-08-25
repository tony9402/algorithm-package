#include <iostream>
#include <unordered_set>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    unordered_set<int> values;
    values.reserve(2 * n);
    for (int index = 0; index < n; ++index) {
        int value;
        cin >> value;
        values.insert(value);
    }

    int queries;
    cin >> queries;
    while (queries--) {
        int value;
        cin >> value;
        cout << (values.find(value) != values.end()) << '\n';
    }
    return 0;
}
