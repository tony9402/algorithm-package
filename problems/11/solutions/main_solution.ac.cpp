#include <iostream>
#include <vector>

using namespace std;

const int MOD = 10007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    vector<int> V(N + 1);
    V[0] = V[1] = 1;
    for(int i = 2; i <= N; ++i) V[i] = (V[i - 1] + V[i - 2]) % MOD;
    cout << V[N];

    return 0;
}
