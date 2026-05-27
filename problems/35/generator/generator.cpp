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
    int maxN = opt<int>("maxN", 100000);
    int n = rnd.next(minN, maxN);
    int minM = opt<int>("minM", 1);
    int maxM = opt<int>("maxM", 100000);
    int m = rnd.next(minM, maxM);

    cout << n << '\n';
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';
        cout << rnd.next(1, 1000);
    }
    cout << '\n' << m << '\n';
    for (int i = 0; i < m; ++i) {
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);
        if (a > b) swap(a, b);
        cout << a << ' ' << b << '\n';
    }
    return 0;
}
