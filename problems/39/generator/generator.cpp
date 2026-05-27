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
    int maxN = opt<int>("maxN", 100);
    string mode = opt<string>("mode", "random");
    int n = rnd.next(minN, maxN);
    int defaultM = mode == "dense" ? min(100000, n * (n - 1) * 3) : min(100000, max(1, n * 4));
    int m = rnd.next(opt<int>("minM", 1), opt<int>("maxM", defaultM));

    cout << n << '\n' << m << '\n';
    set<pair<int, int>> used;
    for (int i = 0; i < m; ++i) {
        int a, b;
        if (mode == "duplicates") {
            a = rnd.next(1, n);
            b = rnd.next(1, n);
            while (a == b) b = rnd.next(1, n);
        } else {
            do {
                a = rnd.next(1, n);
                b = rnd.next(1, n);
            } while (a == b || (!used.insert({a, b}).second && (int)used.size() < n * (n - 1)));
        }
        cout << a << ' ' << b << ' ' << rnd.next(1, 100000) << '\n';
    }
    return 0;
}
