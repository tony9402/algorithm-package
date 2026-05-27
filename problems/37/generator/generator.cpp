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
    registerGen(argc, argv, 1);

    int minV = opt<int>("minV", 2);
    int maxV = opt<int>("maxV", 20000);
    string mode = opt<string>("mode", "random");
    int v = rnd.next(minV, maxV);
    int cut = max(1, v / 2);
    long long possibleEdges = 1LL * v * (v - 1);
    if (mode == "chain") possibleEdges = max(1, v - 1);
    if (mode == "unreachable") possibleEdges -= 1LL * cut * (v - cut);
    int maxPossible = (int)min(300000LL, possibleEdges);
    int defaultMaxE = min(maxPossible, max(1, v * 3));
    int minE = opt<int>("minE", mode == "chain" ? max(1, v - 1) : 1);
    int maxE = opt<int>("maxE", mode == "chain" ? max(1, v - 1) : defaultMaxE);
    minE = min(minE, maxPossible);
    maxE = min(maxE, maxPossible);
    int e = rnd.next(minE, maxE);

    int start = mode == "unreachable" ? 1 : rnd.next(1, v);
    set<pair<int, int>> used;
    vector<tuple<int, int, int>> edges;
    auto add = [&](int a, int b) {
        if (a == b || !used.insert({a, b}).second) return false;
        edges.emplace_back(a, b, rnd.next(1, 10));
        return true;
    };

    if (mode == "chain") {
        for (int i = 1; i < v && (int)edges.size() < e; ++i) add(i, i + 1);
    } else if (mode == "unreachable") {
        for (int i = 1; i < cut && (int)edges.size() < e; ++i) add(i, i + 1);
        while ((int)edges.size() < e) {
            int a = rnd.next(1, v);
            int b = rnd.next(1, v);
            if (a == b) continue;
            if (a <= cut && b > cut) continue;
            add(a, b);
        }
    }
    while ((int)edges.size() < e) {
        int a = rnd.next(1, v);
        int b = rnd.next(1, v);
        if (a != b) add(a, b);
    }

    cout << v << ' ' << edges.size() << '\n';
    cout << start << '\n';
    for (auto [a, b, w] : edges) cout << a << ' ' << b << ' ' << w << '\n';
    return 0;
}
