#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int N, M; cin >> N >> M;
    vector<vector<int>> DP(N + 1, vector<int>(M + 1));
    int width = 0;
    for(int i = 1; i <= N; ++i) {
        string line; cin >> line;
        for(int j = 1; j <= M; ++j) {
            char ch = line[j - 1];
            int offset = (ch == '1' ? 1 : 0);
            DP[i][j] = min({DP[i - 1][j], DP[i - 1][j - 1], DP[i][j - 1]}) + offset;
            width = max(width, DP[i][j]);
        }
    }
    cout << width * width;
    
    return 0;
}
