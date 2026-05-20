#include <iostream>

using namespace std;
using ll = long long;

int V[45][45];
ll DP[45][45][3];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            cin >> V[i][j];
        }
    }

    DP[1][2][0] = 1;
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            int right = V[i][j + 1];
            int down  = V[i + 1][j];
            int bottom_right = V[i + 1][j + 1];
            if(right == 0) {
                DP[i][j + 1][0] += DP[i][j][0] + DP[i][j][2];
            }
            if(down == 0) {
                DP[i + 1][j][1] += DP[i][j][1] + DP[i][j][2];
            }
            if(bottom_right == 0) {
                DP[i + 1][j + 1][2] += DP[i][j][0] + DP[i][j][1] + DP[i][j][2];
            }
        }
    }

    ll ans = DP[N][N][0] + DP[N][N][1] + DP[N][N][2];
    cout << ans;

    return 0;
}
