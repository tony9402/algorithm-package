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
    string mode = opt<string>("mode", "random");
    int n = rnd.next(minN, maxN);

    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    if (mode == "random" || mode == "dense") shuffle(order.begin(), order.end());

    vector<int> pos(n + 1);
    for (int i = 0; i < n; ++i) pos[order[i]] = i;

    vector<vector<int>> prereq(n + 1);
    for (int i = 0; i < n; ++i) {
        int building = order[i];
        if (mode == "chain") {
            if (i > 0) prereq[building].push_back(order[i - 1]);
        } else {
            int limit = mode == "dense" ? i : min(i, 5);
            int cnt = i == 0 ? 0 : rnd.next(0, limit);
            set<int> used;
            while ((int)used.size() < cnt) {
                used.insert(order[rnd.next(0, i - 1)]);
            }
            prereq[building].assign(used.begin(), used.end());
        }
    }

    cout << n << '\n';
    for (int i = 1; i <= n; ++i) {
        cout << rnd.next(1, 100000);
        for (int p : prereq[i]) cout << ' ' << p;
        cout << " -1\n";
    }
    return 0;
}
