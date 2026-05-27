#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int N, M; cin >> N >> M;
    const int INF = 0x3f3f3f3f;
    vector<vector<int>> D(N, vector<int>(N, INF));
    for(int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;
        -- u; -- v;
        D[u][v] = D[v][u] = 1;
    }
    for(int i = 0; i < N; ++i) D[i][i] = 0;
    for(int k = 0; k < N; ++k) {
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                if(i == j || j == k || k == i) continue;
                D[i][j] = min(D[i][k] + D[k][j], D[i][j]);
            }
        }
    }
    int ans = -1, mn = INF;
    for(int i = 0; i < N; ++i) {
        int sum = 0;
        for(int j = 0; j < N; ++j) {
            if(i != j) sum += D[i][j];
        }
        if(mn > sum) mn = sum, ans = i + 1;
    }
    cout << ans;
    
    return 0;
}
