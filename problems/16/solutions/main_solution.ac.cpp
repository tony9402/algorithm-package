#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int N; cin >> N;
    vector<int> V(N);
    for(int i = 0; i < N; ++i) cin >> V[i];
    sort(V.rbegin(), V.rend());
    
    int ans = 0;
    for(int i = 0; i < N; ++i) {
        ans = max(ans, (i + 1) * V[i]);
    }
    cout << ans;

    return 0;
}
