#include "testlib.h"
#include <iostream>
#include <vector>
#include <functional>
#include <queue>
#include <tuple>

using namespace std;

const int dy[] = {-1,1,0,0,-1,-1,1,1};
const int dx[] = {0,0,-1,1,1,-1,1,-1};

void Print(const vector<vector<int>> &V) {
    int N = (int)V.size() - 1;
    cout << N << '\n';
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            cout << V[i][j] << (j == N ? '\n' : ' ');
        }
    }
}

void random_generate(int N) {
    vector<vector<int>> V(N + 1, vector<int>(N + 1));
    
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            V[i][j] = rnd.next(0, 1);
        }
    }
    
    V[1][1] = V[1][2] = 0;
    
    Print(V);
}

void connect_random_generate(int N) {
    vector<vector<int>> V(N + 1, vector<int>(N + 1, 1));
    int K = (N + 1) * (N + 1);
    vector<int> uf(K + 1, -1);
    function<int(int)> find = [&](int x) -> int {
        return uf[x] < 0 ? x : uf[x] = find(uf[x]);
    };
    function<bool(int, int)> merge = [&](int u, int v) -> bool {
        u = find(u);
        v = find(v);
        if(u == v) return false;
        uf[v] = u;
        return true;
    };
    function<int(int, int)> pos = [&](int y, int x) -> int {
        return y * (N + 1) + x;
    };
    
    V[1][1] = V[1][2] = V[N][N] = 0;
    priority_queue<tuple<int, int, int>> pq;
    vector<vector<int>> visited(N + 1, vector<int>(N + 1));
    pq.emplace(rnd.next(0, 100000), 1, 1); 
    visited[1][1] = 1;
    pq.emplace(rnd.next(0, 100000), N, N);
    visited[N][N] = 1;

    while(!pq.empty() && find(pos(1, 1)) != find(pos(N, N))) {
        auto [_, y, x] = pq.top(); pq.pop();
        for(int k = 0; k < 8; ++k) {
            int qy = y + dy[k];
            int qx = x + dx[k];
            if(1 > qy || qy > N || 1 > qx || qx > N) continue;
            if(visited[qy][qx]) continue;
            visited[qy][qx] = 1;
            pq.emplace(rnd.next(0, 100000), qy, qx);
            merge(pos(y, x), pos(qy, qx));
        }
    }
    
    Print(V);
}

void large_answer_generate(int N) {
    vector<vector<int>> V(N + 1, vector<int>(N + 1, 0));
    Print(V);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int minN = opt<int>("minN", 3);
    int maxN = opt<int>("maxN", 32);
    string mode = opt<string>("mode", "random");

    int N = rnd.next(minN, maxN);    
    if(mode == "random") {
        random_generate(N);
    }
    else if(mode == "connect_random") {
        connect_random_generate(N);
    }
    else if(mode == "large_answer") {
        large_answer_generate(maxN);
    }
    
    return 0;
}
