#include "testlib.h"
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

void Print(int N, const vector<pair<int, int>> &edges) {
    int M = (int)edges.size();
    cout << N << ' ' << M << '\n';
    for(const auto &[u, v]: edges) cout << u << ' ' << v << '\n';
}

// 연결 그래프이어야 함.
void random_generate(int N, int M) {
    vector<int> node = rnd.perm(N, 1);
    vector<pair<int, int>> edges;
    int remain = M - N + 1;
    
    for(int i = 1; i < N; ++i) {
        int idx = rnd.next(0, i - 1);
        edges.emplace_back(node[idx], node[i]);
    }
    
    for(int i = 0; i < remain; ++i) {
        int u = rnd.next(1, N - 1);
        int v = rnd.next(u + 1, N);
        if(rnd.next(0, 1)) swap(u, v);
        edges.emplace_back(u, v);
    }
    
    Print(N, edges);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int minN = opt<int>("minN", 2);
    int maxN = opt<int>("maxN", 100);
    int minM = opt<int>("minM", 1);
    int maxM = opt<int>("maxM", 5000);
    string mode = opt<string>("mode", "random");
    
    int N = rnd.next(minN, maxN);
    minM = max(N - 1, minM);
    int M = rnd.next(minM, maxM);
    if(mode == "random") {
        random_generate(N, M);
    }

    return 0;
}
