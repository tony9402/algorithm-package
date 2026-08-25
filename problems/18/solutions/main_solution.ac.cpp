#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int, int>> lectures(n);
    for (auto& [deadline, pay] : lectures) {
        cin >> pay >> deadline;
    }
    sort(lectures.begin(), lectures.end());

    priority_queue<int, vector<int>, greater<int>> selected;
    for (auto [deadline, pay] : lectures) {
        selected.push(pay);
        if (static_cast<int>(selected.size()) > deadline) {
            selected.pop();
        }
    }

    long long answer = 0;
    while (!selected.empty()) {
        answer += selected.top();
        selected.pop();
    }
    cout << answer << '\n';
}
