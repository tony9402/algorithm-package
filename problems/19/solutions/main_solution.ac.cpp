#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> original(n);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            int x;
            cin >> x;
            if (x) original[r] |= 1 << c;
        }
    }

    const int limit = (1 << n) - 1;
    auto sameRow = [&](int mask) {
        return (mask ^ ((mask << 1) & limit) ^ (mask >> 1)) & limit;
    };

    int answer = n * n + 1;
    for (int first = 0; first <= limit; ++first) {
        vector<int> board = original;
        int count = __builtin_popcount((unsigned)first);
        board[0] ^= sameRow(first);
        if (n > 1) board[1] ^= first;

        for (int r = 1; r < n; ++r) {
            int press = board[r - 1];
            count += __builtin_popcount((unsigned)press);
            board[r - 1] ^= press;
            board[r] ^= sameRow(press);
            if (r + 1 < n) board[r + 1] ^= press;
        }
        if (board[n - 1] == 0) answer = min(answer, count);
    }

    cout << (answer == n * n + 1 ? -1 : answer) << '\n';
    return 0;
}
