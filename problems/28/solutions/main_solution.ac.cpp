#include <algorithm>
#include <array>
#include <climits>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> pop(n);
    int total = 0;
    for (int& x : pop) {
        cin >> x;
        total += x;
    }

    vector<vector<int>> g(n);
    for (int i = 0; i < n; ++i) {
        int cnt;
        cin >> cnt;
        while (cnt--) {
            int v;
            cin >> v;
            g[i].push_back(v - 1);
        }
    }

    auto connected = [&](int mask) {
        int start = -1;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                start = i;
                break;
            }
        }
        if (start == -1) return false;

        int seen = 0;
        queue<int> q;
        q.push(start);
        seen |= 1 << start;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int nxt : g[cur]) {
                if ((mask & (1 << nxt)) && !(seen & (1 << nxt))) {
                    seen |= 1 << nxt;
                    q.push(nxt);
                }
            }
        }
        return seen == mask;
    };

    int answer = INT_MAX;
    int full = (1 << n) - 1;
    for (int mask = 1; mask < full; ++mask) {
        if (!connected(mask) || !connected(full ^ mask)) continue;
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) sum += pop[i];
        }
        answer = min(answer, abs(total - 2 * sum));
    }

    cout << (answer == INT_MAX ? -1 : answer) << '\n';
    return 0;
}
