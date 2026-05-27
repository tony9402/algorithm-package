#include "testlib.h"
#include <vector>
#include <functional>
#include <algorithm>
 
using namespace std;
 
#define MAXN 100000
 
int main(int argc, char **argv) {
    registerValidation(argc, argv);
 
    int N = inf.readInt(1, MAXN, "N");
    inf.readEoln();
    vector<int> color(N + 1);
    vector<vector<int>> graph(N + 1);
    for(int i = 1; i <= N; i++) {
        color[i] = inf.readInt(0, N, "Color");
        if(i == N) inf.readEoln();
        else inf.readSpace();
    }
    for(int i = 0; i + 1 < N; i++) {
        int a = inf.readInt(1, N, "u"); inf.readSpace();
        int b = inf.readInt(1, N, "v"); inf.readEoln();
        ensure(a != b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    function<void(int, int, int)> dfs = [&](int cur, int prev, int c) -> void {
        if(c) ensure(color[cur] != 0);
        if(color[cur]) c = 1;
        for(int nxt : graph[cur]) {
            if(nxt == prev) continue;
            dfs(nxt, cur, c);
        }
    };
    dfs(1, 0, 0);
    inf.readEof();
}
