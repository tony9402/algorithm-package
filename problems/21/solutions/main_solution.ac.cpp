#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, C; cin >> N >> C;
    vector<int> V(N);
    for(int i = 0; i < N; ++i) cin >> V[i];
    sort(V.begin(), V.end());

    int lo = 1, hi = 1'000'000'000;
    while(lo <= hi) {
        int mid = (lo + hi) / 2;
        int cnt = 1, cur = V[0];
        for(int i = 1; i < N; ++i) {
            if(V[i] - cur >= mid) ++ cnt, cur = V[i];
        }
        if(cnt >= C) lo = mid + 1;
        else hi = mid - 1;
    }
    cout << hi;

    return 0;
}
