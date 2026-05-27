#include "testlib.h"
#include <algorithm>
#include <array>
#include <climits>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 32000, "N");
    inf.readSpace();
    int m = inf.readInt(0, 100000, "M");
    inf.readEoln();

    vector<vector<int>> graph(n + 1);
    vector<int> indegree(n + 1);
    set<pair<int, int>> seen;
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "A");
        inf.readSpace();
        int b = inf.readInt(1, n, "B");
        inf.readEoln();
        ensuref(a != b, "self constraint at %d", a);
        ensuref(seen.insert({a, b}).second, "duplicated constraint %d -> %d", a, b);
        graph[a].push_back(b);
        ++indegree[b];
    }

    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (indegree[i] == 0) q.push(i);
    }
    int visited = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        ++visited;
        for (int nxt : graph[cur]) {
            if (--indegree[nxt] == 0) q.push(nxt);
        }
    }
    ensuref(visited == n, "constraints must form a DAG");
    inf.readEof();
    return 0;
}
