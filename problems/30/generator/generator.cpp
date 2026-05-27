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

void print_edges(int n, const vector<pair<int, int>>& edges) {
    cout << n << '\n';
    for (auto [a, b] : edges) cout << a << ' ' << b << '\n';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int minN = opt<int>("minN", 2);
    int maxN = opt<int>("maxN", 1000000);
    string mode = opt<string>("mode", "random");
    int n = rnd.next(minN, maxN);

    vector<pair<int, int>> edges;
    edges.reserve(n - 1);

    if (mode == "chain") {
        for (int i = 1; i < n; ++i) edges.emplace_back(i, i + 1);
    } else if (mode == "star") {
        for (int i = 2; i <= n; ++i) edges.emplace_back(1, i);
    } else if (mode == "binary") {
        for (int i = 2; i <= n; ++i) edges.emplace_back(i / 2, i);
    } else {
        for (int i = 2; i <= n; ++i) {
            edges.emplace_back(rnd.next(1, i - 1), i);
        }
        shuffle(edges.begin(), edges.end());
    }

    print_edges(n, edges);
    return 0;
}
