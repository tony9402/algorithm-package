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

struct DSU {
    vector<int> p;
    explicit DSU(int n) : p(n + 1, -1) {}
    int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }
    bool merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (p[a] > p[b]) swap(a, b);
        p[a] += p[b];
        p[b] = a;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000000, "N");
    inf.readEoln();

    DSU dsu(n);
    for (int i = 0; i < n - 1; ++i) {
        int a = inf.readInt(1, n, "u");
        inf.readSpace();
        int b = inf.readInt(1, n, "v");
        inf.readEoln();
        ensuref(a != b, "self edge at %d", a);
        ensuref(dsu.merge(a, b), "edge %d creates a cycle", i + 1);
    }
    inf.readEof();
    return 0;
}
