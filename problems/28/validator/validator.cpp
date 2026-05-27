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

    int n = inf.readInt(2, 10, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 100, "population");
        if (i == n) inf.readEoln();
        else inf.readSpace();
    }

    vector<vector<int>> g(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i) {
        int cnt = inf.readInt(0, n - 1, "adjacent_count");
        set<int> seen;
        for (int j = 0; j < cnt; ++j) {
            inf.readSpace();
            int v = inf.readInt(1, n, "adjacent_area");
            ensuref(v != i, "self adjacency at area %d", i);
            ensuref(seen.insert(v).second, "duplicated adjacent area %d in row %d", v, i);
            g[i][v] = 1;
        }
        inf.readEoln();
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            ensuref(g[i][j] == g[j][i], "adjacency is not symmetric between %d and %d", i, j);
        }
    }
    inf.readEof();
    return 0;
}
