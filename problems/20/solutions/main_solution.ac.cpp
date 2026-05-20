#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    vector<int> V(N);
    for(int i = 0; i < N; ++i) cin >> V[i];
    sort(V.begin(), V.end());

    int M; cin >> M;
    for(int i = 0; i < M; ++i) {
        int x; cin >> x;
        if(binary_search(V.begin(), V.end(), x)) cout << 1 << '\n';
        else cout << 0 << '\n';
    }

    return 0;
}
