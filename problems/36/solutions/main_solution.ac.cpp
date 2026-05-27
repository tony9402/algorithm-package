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
    vector<vector<int>> pref(n + 1, vector<int>(n + 1));
    int answer = -1000 * 300 * 300 - 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int x;
            cin >> x;
            pref[i][j] = x + pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
        }
    }

    for (int len = 1; len <= n; ++len) {
        for (int r = len; r <= n; ++r) {
            for (int c = len; c <= n; ++c) {
                int sum = pref[r][c] - pref[r - len][c] - pref[r][c - len] + pref[r - len][c - len];
                answer = max(answer, sum);
            }
        }
    }

    cout << answer << '\n';
    return 0;
}
