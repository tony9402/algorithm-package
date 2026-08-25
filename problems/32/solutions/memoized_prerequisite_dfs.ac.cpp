#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> cost(n + 1);
    vector<vector<int>> prerequisites(n + 1);
    for (int building = 1; building <= n; ++building) {
        cin >> cost[building];
        while (true) {
            int prerequisite;
            cin >> prerequisite;
            if (prerequisite == -1) {
                break;
            }
            prerequisites[building].push_back(prerequisite);
        }
    }

    vector<int> completion(n + 1, -1);
    function<int(int)> calculate = [&](int building) {
        if (completion[building] != -1) {
            return completion[building];
        }
        int prerequisite_time = 0;
        for (int prerequisite : prerequisites[building]) {
            prerequisite_time = max(prerequisite_time, calculate(prerequisite));
        }
        completion[building] = prerequisite_time + cost[building];
        return completion[building];
    };

    for (int building = 1; building <= n; ++building) {
        cout << calculate(building) << '\n';
    }
}
