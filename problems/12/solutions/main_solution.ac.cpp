#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    vector<int> V(N + 1);
    for(int i = 1; i <= N; ++i) cin >> V[i];
    vector<int> DP(N + 1, -1);
    DP[0] = 0;

    function<int(int)> go = [&](int x) -> int {
        if(x < 0) return 0;
        int &ret = DP[x];
        if(ret != -1) return ret;
        ret = max(V[x - 1] + go(x - 3), go(x - 2)) + V[x];
        return ret;
    };

    cout << go(N);
    return 0;
}
