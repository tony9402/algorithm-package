#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int findAvailable(int day, vector<int>& parent) {
    int root = day;
    while (root != parent[root]) {
        root = parent[root];
    }
    while (day != root) {
        int next = parent[day];
        parent[day] = root;
        day = next;
    }
    return root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int, int>> lectures(n);
    int maximum_day = 0;
    for (auto& [pay, day] : lectures) {
        cin >> pay >> day;
        maximum_day = max(maximum_day, day);
    }
    sort(lectures.begin(), lectures.end(), greater<pair<int, int>>());

    vector<int> parent(maximum_day + 1);
    iota(parent.begin(), parent.end(), 0);
    long long answer = 0;
    for (auto [pay, deadline] : lectures) {
        int day = findAvailable(deadline, parent);
        if (day == 0) {
            continue;
        }
        answer += pay;
        parent[day] = findAvailable(day - 1, parent);
    }

    cout << answer << '\n';
}
