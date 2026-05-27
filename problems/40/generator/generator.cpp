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

string random_word(int max_len, int alphabet) {
    int len = rnd.next(1, max_len);
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) s.push_back(char('a' + rnd.next(0, alphabet - 1)));
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int minN = opt<int>("minN", 1);
    int maxN = opt<int>("maxN", 10000);
    int minM = opt<int>("minM", 1);
    int maxM = opt<int>("maxM", 10000);
    string mode = opt<string>("mode", "random");
    int maxLen = opt<int>("maxLen", 20);
    int n = rnd.next(minN, maxN);
    int m = rnd.next(minM, maxM);

    set<string> used;
    vector<string> words;
    while ((int)words.size() < n) {
        string s;
        if (mode == "prefix_heavy") {
            s = string(rnd.next(1, min(maxLen, 30)), char('a' + rnd.next(0, 2)));
            if (rnd.next(0, 1)) s += random_word(max(1, maxLen / 2), 3);
            if ((int)s.size() > 500) s.resize(500);
        } else {
            s = random_word(maxLen, 26);
        }
        if (used.insert(s).second) words.push_back(s);
    }

    cout << n << ' ' << m << '\n';
    for (const string& s : words) cout << s << '\n';
    for (int i = 0; i < m; ++i) {
        if (rnd.next(0, 99) < 60) {
            const string& base = words[rnd.next(0, n - 1)];
            cout << base.substr(0, rnd.next(1, (int)base.size())) << '\n';
        } else {
            cout << random_word(maxLen, mode == "prefix_heavy" ? 3 : 26) << '\n';
        }
    }
    return 0;
}
