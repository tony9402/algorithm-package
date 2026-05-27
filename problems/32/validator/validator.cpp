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

    int n = inf.readInt(1, 500, "N");
    inf.readEoln();

    vector<vector<int>> graph(n + 1);
    vector<int> indegree(n + 1);
    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 100000, "time");
        set<int> seen;
        while (true) {
            inf.readSpace();
            int p = inf.readInt(-1, n, "prerequisite");
            if (p == -1) break;
            ensuref(p != i, "building %d depends on itself", i);
            ensuref(seen.insert(p).second, "duplicated prerequisite %d for building %d", p, i);
            graph[p].push_back(i);
            ++indegree[i];
        }
        inf.readEoln();
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
    ensuref(visited == n, "prerequisites must form a DAG");
    inf.readEof();
    return 0;
}
