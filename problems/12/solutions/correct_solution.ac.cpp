#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> stairs;
// 1. Top Down
vector<vector<int>> cache;

int score_memoization(int n, int step) {
    if(n < 0) return 0;
    if(cache[step][n] != -1) return cache[step][n];
    cache[step][n] = stairs[n] + max(step == 2 ? score_memoization(n - 1, 1) : -0x3f3f3f3f, score_memoization(n - 2, 2));
    return cache[step][n];
}

int main() {
    // 빠른 입출력을 위해 사용합니다.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;

    cache.resize(3, vector<int>(n, -1));

    for(int num = 0; num < n; ++num) {
        int x; cin >> x;
        stairs.push_back(x);
    }

    cout << score_memoization(n - 1, 2);

    return 0;
}