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

void read_permutation(int n, const string& name) {
    vector<int> seen(n + 1);
    for (int i = 1; i <= n; ++i) {
        int value = inf.readInt(1, n, name.c_str());
        ensuref(!seen[value], "%s contains duplicated value %d", name.c_str(), value);
        seen[value] = 1;
        if (i == n) inf.readEoln();
        else inf.readSpace();
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();
    read_permutation(n, "inorder");
    read_permutation(n, "postorder");
    inf.readEof();
    return 0;
}
