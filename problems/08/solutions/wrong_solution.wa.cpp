#include <iostream>
#include <deque>
#include <vector>

using namespace std;

const int MAX = 100000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, K; cin >> N >> K;
    
    deque<int> dq;
    vector<int> dist(MAX + 1, -1);

    dist[N] = 0;
    dq.push_back(N);
    
    while(!dq.empty()) {
        int cur = dq.front(); dq.pop_front();
        if(2 * cur < MAX && dist[2 * cur] == -1) dist[2 * cur] = dist[cur], dq.push_front(2 * cur);
        for(int d : {-1, 1}) {
            int nxt = cur + d;
            if(0 > nxt || nxt > MAX) continue;
            if(dist[nxt] != -1) continue;
            dist[nxt] = dist[cur] + 1;
            dq.push_back(nxt);
        }
    }
    cout << dist[K];

    return 0;
}
