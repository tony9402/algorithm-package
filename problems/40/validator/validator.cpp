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

    int n = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 10000, "M");
    inf.readEoln();

    set<string> seen;
    for (int i = 0; i < n; ++i) {
        string s = inf.readToken("[a-z]{1,500}", "S");
        ensuref(seen.insert(s).second, "duplicated set string: %s", s.c_str());
        inf.readEoln();
    }
    for (int i = 0; i < m; ++i) {
        inf.readToken("[a-z]{1,500}", "query");
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
