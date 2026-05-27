#include "testlib.h"
#include <vector>
#include <functional>

using namespace std;

// 무방향 그래프 이면서 연결 그래프이어야 하는 조건도 있음.

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    int N = inf.readInt(2, 100); inf.readSpace();
    int M = inf.readInt(1, 5000);
    inf.readEoln();
    
    vector<int> uf(N + 1, -1), siz(N + 1, 1);
    
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
    
    for(int i = 0; i < M; ++i) {
        int u = inf.readInt(1, N); inf.readSpace();
        int v = inf.readInt(1, N);
        inf.readEoln();

        ensuref(u != v, "Must be u != v");
        merge(u, v);
    }
    ensuref(siz[find(1)] == N, "Must be Connected Graph");
    inf.readEof();
    
    return 0;
}
