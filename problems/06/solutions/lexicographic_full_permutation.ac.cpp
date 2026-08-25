#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numberCount, prefixLength;
    cin >> numberCount >> prefixLength;
    vector<int> permutation(numberCount);
    iota(permutation.begin(), permutation.end(), 1);

    do {
        if (!is_sorted(permutation.begin() + prefixLength, permutation.end())) {
            continue;
        }
        for (int i = 0; i < prefixLength; ++i) {
            cout << permutation[i] << ' ';
        }
        cout << '\n';
    } while (next_permutation(permutation.begin(), permutation.end()));
    return 0;
}
