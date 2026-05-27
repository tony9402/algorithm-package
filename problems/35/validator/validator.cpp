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

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();
    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 1000, "value");
        if (i == n) inf.readEoln();
        else inf.readSpace();
    }
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "i");
        inf.readSpace();
        int b = inf.readInt(1, n, "j");
        inf.readEoln();
        ensuref(a <= b, "query start must be <= end");
    }
    inf.readEof();
    return 0;
}
