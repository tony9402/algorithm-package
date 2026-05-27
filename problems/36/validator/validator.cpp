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

    int n = inf.readInt(1, 300, "N");
    inf.readEoln();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            inf.readInt(-1000, 1000, "profit");
            if (j == n) inf.readEoln();
            else inf.readSpace();
        }
    }
    inf.readEof();
    return 0;
}
