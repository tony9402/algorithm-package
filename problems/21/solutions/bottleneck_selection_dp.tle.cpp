#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, router_count;
    cin >> n >> router_count;
    vector<int> house(n);
    for (int &position : house) {
        cin >> position;
    }
    sort(house.begin(), house.end());

    const int infinity = 1'000'000'001;
    vector<int> previous(n, infinity), current(n);
    for (int placed = 2; placed <= router_count; ++placed) {
        fill(current.begin(), current.end(), -1);
        for (int last = placed - 1; last < n; ++last) {
            for (int before = placed - 2; before < last; ++before) {
                current[last] = max(
                    current[last],
                    min(previous[before], house[last] - house[before])
                );
            }
        }
        previous.swap(current);
    }

    cout << *max_element(previous.begin(), previous.end()) << '\n';
    return 0;
}
