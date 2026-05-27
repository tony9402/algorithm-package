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
    int maxN = opt<int>("maxN", 300);
    string mode = opt<string>("mode", "random");
    int n = rnd.next(minN, maxN);

    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j) cout << ' ';
            int value;
            if (mode == "negative") value = rnd.next(-1000, -1);
            else if (mode == "positive") value = rnd.next(1, 1000);
            else value = rnd.next(-1000, 1000);
            cout << value;
        }
        cout << '\n';
    }
    return 0;
}
