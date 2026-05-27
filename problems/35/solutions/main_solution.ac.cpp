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
    vector<int> pref(n + 1);
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        pref[i] = pref[i - 1] + x;
    }

    int m;
    cin >> m;
    while (m--) {
        int a, b;
        cin >> a >> b;
        cout << pref[b] - pref[a - 1] << '\n';
    }
    return 0;
}
