#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int N, M; cin >> N >> M;
    vector<int> V(N + 1), psum(N + 1);
    for(int i = 1; i <= N; ++i) {
        cin >> V[i];
        psum[i] = psum[i - 1] + V[i];
    }
    int answer = 0;
    for(int i = 1, r = 0; i <= N; ++i) {
        while(r + 1 <= N && psum[r + 1] - psum[i - 1] <= M) ++ r;
        if(psum[r] - psum[i - 1] == M) ++ answer;
    }
    cout << answer;
    return 0;
}
