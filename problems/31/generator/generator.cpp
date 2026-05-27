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

    int minN = opt<int>("minN", 2);
    int maxN = opt<int>("maxN", 32000);
    string mode = opt<string>("mode", "random");
    int n = rnd.next(minN, maxN);
    int defaultMaxM = min(100000, max(1, n * 3));
    int minM = opt<int>("minM", mode == "chain" ? n - 1 : 1);
    int maxM = opt<int>("maxM", mode == "chain" ? n - 1 : defaultMaxM);
    int maxPossible = min(100000LL, 1LL * n * (n - 1) / 2);
    minM = min(minM, maxPossible);
    maxM = min(maxM, maxPossible);
    int m = rnd.next(minM, maxM);

    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    shuffle(order.begin(), order.end());

    set<pair<int, int>> edges;
    if (mode == "chain") {
        for (int i = 0; i + 1 < n; ++i) edges.emplace(order[i], order[i + 1]);
    }
    while ((int)edges.size() < m) {
        int a = rnd.next(0, n - 2);
        int b = rnd.next(a + 1, n - 1);
        edges.emplace(order[a], order[b]);
    }

    cout << n << ' ' << edges.size() << '\n';
    for (auto [a, b] : edges) cout << a << ' ' << b << '\n';
    return 0;
}
