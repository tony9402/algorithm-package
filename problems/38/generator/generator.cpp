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

    int minN = opt<int>("minN", 1);
    int maxN = opt<int>("maxN", 500);
    string mode = opt<string>("mode", "dag");
    int n = rnd.next(minN, maxN);
    int maxM = opt<int>("maxM", 6000);
    int minM = opt<int>("minM", 1);

    if (n == 1) {
        cout << "1 1\n1 1 0\n";
        return 0;
    }

    vector<tuple<int, int, int>> edges;
    set<pair<int, int>> used;
    auto add_unique = [&](int a, int b, int c) {
        if (a == b || !used.insert({a, b}).second) return false;
        edges.emplace_back(a, b, c);
        return true;
    };

    if (mode == "negative_cycle" && n >= 2) {
        add_unique(1, 2, -1);
        add_unique(2, 1, -1);
    } else if (mode == "unreachable" && n >= 2) {
        add_unique(2, 1, rnd.next(-10, 10));
    }

    long long possible = 1LL * n * (n - 1);
    if (mode == "dag") possible = 1LL * n * (n - 1) / 2;
    if (mode == "unreachable") possible = 1LL * (n - 1) * (n - 1);
    int targetMax = min<long long>(maxM, possible);
    targetMax = max(targetMax, (int)edges.size());
    int targetMin = min(minM, targetMax);
    int target = rnd.next(targetMin, targetMax);
    target = max(target, (int)edges.size());

    int attempts = 0;
    while ((int)edges.size() < target && attempts < 200000) {
        ++attempts;
        if (mode == "dag") {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n);
            if (a == b) continue;
            if (a > b) swap(a, b);
            add_unique(a, b, rnd.next(-10000, 10000));
        } else if (mode == "unreachable") {
            if (n == 1) break;
            int a = rnd.next(2, n);
            int b = rnd.next(1, n);
            if (a != b) add_unique(a, b, rnd.next(-10000, 10000));
        } else {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n);
            if (a != b) add_unique(a, b, rnd.next(-10000, 10000));
        }
    }

    cout << n << ' ' << edges.size() << '\n';
    for (auto [a, b, c] : edges) cout << a << ' ' << b << ' ' << c << '\n';
    return 0;
}
