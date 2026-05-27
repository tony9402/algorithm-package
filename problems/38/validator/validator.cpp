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

    int n = inf.readInt(1, 500, "N");
    inf.readSpace();
    int m = inf.readInt(1, 6000, "M");
    inf.readEoln();
    for (int i = 0; i < m; ++i) {
        inf.readInt(1, n, "A");
        inf.readSpace();
        inf.readInt(1, n, "B");
        inf.readSpace();
        inf.readInt(-10000, 10000, "C");
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
