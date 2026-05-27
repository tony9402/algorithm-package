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

    int v = inf.readInt(1, 20000, "V");
    inf.readSpace();
    int e = inf.readInt(1, 300000, "E");
    inf.readEoln();
    inf.readInt(1, v, "K");
    inf.readEoln();
    for (int i = 0; i < e; ++i) {
        int a = inf.readInt(1, v, "u");
        inf.readSpace();
        int b = inf.readInt(1, v, "v");
        inf.readSpace();
        inf.readInt(1, 10, "w");
        inf.readEoln();
        ensuref(a != b, "self edge at %d", a);
    }
    inf.readEof();
    return 0;
}
