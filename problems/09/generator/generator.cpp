#include "testlib.h"
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <numeric>
#include <algorithm>

using namespace std;

const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};

void random_generate(int N, int M) {
    vector<vector<int>> V(N, vector<int>(N, 0));
    vector<int> idx(N * N);
    iota(idx.begin(), idx.end(), 0);
    shuffle(idx.begin(), idx.end());

    int K = rnd.next(0, N * N - M);
    for(int i = 0; i < K; ++i) {
        int y = idx[i] / N;
        int x = idx[i] % N;
        V[y][x] = 1;
    }
    for(int i = 0; i < M; ++i) {
        int y = idx[K + i] / N;
        int x = idx[K + i] % N;
        V[y][x] = 2;
    }

    cout << N << ' ' << M << '\n';
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cout << V[i][j];
            if(j + 1 == N) cout << '\n';
            else cout << ' ';
        }
    }
}

// 항상 답이 -1이 아닌 랜덤 데이터
void random_generate_version_2(int N, int M) {
    vector<vector<int>> V(N, vector<int>(N, 1));
    vector<int> uf(N * N, -1);
    vector<int> siz(N * N);
    function<int(int)> find = [&](int x) -> int {
        return uf[x] < 0 ? x : uf[x] = find(uf[x]);
    };
    function<bool(int, int)> merge = [&](int u, int v) -> bool {
        u = find(u); v = find(v);
        if(u == v) return false;
        uf[v] = u;
        siz[u] += siz[v];
        return true;
    };

    vector<int> idx(N * N, 0);
    iota(idx.begin(), idx.end(), 0);
    shuffle(idx.begin(), idx.end());
    int K = rnd.next(M, 10);

    vector<pair<int, int>> start_points;
    for(int i = 0; i < K; ++i) {
        int y = idx[i] / N, x = idx[i] % N;
        V[y][x] = 2;
        siz[idx[i]] = 1;
        start_points.emplace_back(y, x);
    }

    priority_queue<tuple<int, int, int>> pq;
    for(const auto &[y, x]: start_points) {
        int weight = rnd.next(1, 100000);
        pq.emplace(weight, y, x);
    }
    while(!pq.empty() && siz[find(idx[0])] == K) {
        auto [_, y, x] = pq.top(); pq.pop();
        for(int k = 0; k < 4; ++k) {
            int qy = y + dy[k], qx = x + dx[k];
            if(0 > qy || qy >= N || 0 > qx || qx >= N) continue;
            if(V[qy][qx] != 1) continue;
            V[qy][qx] = 0;
            merge(qy * N + qx, y * N + x);
            int weight = rnd.next(1, 100000);
            pq.emplace(weight, qy, qx);
        }
    }

    cout << N << " " << M << '\n';
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cout << V[i][j] << (j + 1 == N ? '\n' : ' ');
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int minN = opt<int>("minN", 4);
    int maxN = opt<int>("maxN", 50);
    int minM = opt<int>("minM", 1);
    int maxM = opt<int>("maxM", 10);
    string mode = opt<string>("mode", "random");

    if(mode == "random") {
        int N = rnd.next(minN, maxN);
        int M = rnd.next(minM, maxM);
        random_generate(N, M);
    }
    else if(mode == "random_v2") {
        int N = rnd.next(minN, maxN);
        int M = rnd.next(minM, maxM);
        random_generate_version_2(N, M);
    }

    return 0;
}
