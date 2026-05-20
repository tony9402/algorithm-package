#include <iostream>
#include <vector>
#include <utility>
#include <numeric>
#include <algorithm>

using namespace std;

const int MAX = 10000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    vector<int> mx(MAX + 1);
    for(int i = 0; i < N; ++i) {
        int p, d; cin >> p >> d;
        mx[d] = max(mx[d], p);
    }
    cout << accumulate(mx.begin(), mx.end(), 0);

    return 0;
}
