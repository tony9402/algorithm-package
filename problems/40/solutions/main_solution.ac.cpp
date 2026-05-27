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

    int n, m;
    cin >> n >> m;
    vector<string> words(n);
    for (string& s : words) cin >> s;
    sort(words.begin(), words.end());

    int answer = 0;
    while (m--) {
        string q;
        cin >> q;
        auto it = lower_bound(words.begin(), words.end(), q);
        if (it != words.end() && it->compare(0, q.size(), q) == 0) ++answer;
    }
    cout << answer << '\n';
    return 0;
}
