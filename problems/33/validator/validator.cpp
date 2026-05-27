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

    int n = inf.readInt(1, 64, "N");
    inf.readEoln();
    ensuref((n & (n - 1)) == 0, "N must be a power of two");

    for (int i = 0; i < n; ++i) {
        string row = inf.readToken("[01]+", "row");
        ensuref((int)row.size() == n, "row %d length is %d, expected %d", i + 1, (int)row.size(), n);
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
