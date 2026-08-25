#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int, int>> lectures(n);
    int maximum_day = 0;
    for (auto& [deadline, pay] : lectures) {
        cin >> pay >> deadline;
        maximum_day = max(maximum_day, deadline);
    }
    sort(lectures.begin(), lectures.end());

    int maximum_count = min(n, maximum_day);
    map<int, long long> best;
    for (int count = 0; count <= maximum_count; ++count) {
        best.emplace(count, -1);
    }
    best.at(0) = 0;

    int considered = 0;
    for (auto [deadline, pay] : lectures) {
        ++considered;
        int limit = min({considered, deadline, maximum_count});
        for (int count = limit; count >= 1; --count) {
            if (best.at(count - 1) != -1) {
                best.at(count) = max(best.at(count),
                                     best.at(count - 1) + pay);
            }
        }
    }

    long long answer = 0;
    for (const auto& [count, pay] : best) {
        answer = max(answer, pay);
    }
    cout << answer << '\n';
}
