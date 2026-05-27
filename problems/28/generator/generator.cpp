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

void add_edge(vector<vector<int>>& g, int a, int b) {
    if (a == b || g[a][b]) return;
    g[a][b] = g[b][a] = 1;
}

void add_random_tree(vector<vector<int>>& g, const vector<int>& nodes) {
    for (int i = 1; i < (int)nodes.size(); ++i) {
        int p = nodes[rnd.next(0, i - 1)];
        add_edge(g, nodes[i], p);
    }
}

void print_case(int n, const vector<int>& pop, const vector<vector<int>>& g) {
    cout << n << '\n';
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';
        cout << pop[i];
    }
    cout << '\n';

    for (int i = 1; i <= n; ++i) {
        vector<int> adj;
        for (int j = 1; j <= n; ++j) {
            if (g[i][j]) adj.push_back(j);
        }
        cout << adj.size();
        for (int v : adj) cout << ' ' << v;
        cout << '\n';
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int minN = opt<int>("minN", 2);
    int maxN = opt<int>("maxN", 10);
    string mode = opt<string>("mode", "random");
    int n = rnd.next(minN, maxN);

    vector<int> pop(n + 1);
    for (int i = 1; i <= n; ++i) pop[i] = rnd.next(1, 100);

    vector<vector<int>> g(n + 1, vector<int>(n + 1));
    if (mode == "connected") {
        vector<int> nodes(n);
        iota(nodes.begin(), nodes.end(), 1);
        shuffle(nodes.begin(), nodes.end());
        add_random_tree(g, nodes);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next(0, 99) < 25) add_edge(g, i, j);
            }
        }
    } else if (mode == "disconnected") {
        int cut = rnd.next(1, n - 1);
        vector<int> left, right;
        for (int i = 1; i <= n; ++i) {
            if (i <= cut) left.push_back(i);
            else right.push_back(i);
        }
        add_random_tree(g, left);
        add_random_tree(g, right);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if ((i <= cut) == (j <= cut) && rnd.next(0, 99) < 30) add_edge(g, i, j);
            }
        }
    } else if (mode == "isolated") {
        // Intentionally leave every area isolated.
    } else {
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next(0, 99) < 35) add_edge(g, i, j);
            }
        }
    }

    print_case(n, pop, g);
    return 0;
}
