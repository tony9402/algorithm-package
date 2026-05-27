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

string random_name(int max_len, int alphabet) {
    int len = rnd.next(1, max_len);
    string s;
    for (int i = 0; i < len; ++i) s.push_back(char('a' + rnd.next(0, alphabet - 1)));
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int minN = opt<int>("minN", 1);
    int maxN = opt<int>("maxN", 100000);
    string mode = opt<string>("mode", "random");
    int n = rnd.next(minN, maxN);

    vector<string> base;
    for (int i = 0; i < 100; ++i) base.push_back(random_name(10, 5));

    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        string s;
        if (mode == "duplicates") {
            s = base[rnd.next(0, (int)base.size() - 1)];
        } else if (mode == "prefixes") {
            int len = rnd.next(1, 10);
            s.assign(len, 'a');
            if (rnd.next(0, 2) == 0) s.back() = char('a' + rnd.next(0, 2));
        } else {
            s = random_name(10, 26);
        }
        cout << s << '\n';
    }
    return 0;
}
