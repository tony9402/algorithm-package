#include <iostream>
#include <string>
#include <vector>

using namespace std;

string encode(int row, int column, int length,
              const vector<vector<int>>& prefix) {
    int bottom = row + length;
    int right = column + length;
    int ones = prefix[bottom][right] - prefix[row][right] -
               prefix[bottom][column] + prefix[row][column];
    if (ones == 0) {
        return "0";
    }
    if (ones == length * length) {
        return "1";
    }

    int half = length / 2;
    return "(" + encode(row, column, half, prefix) +
           encode(row, column + half, half, prefix) +
           encode(row + half, column, half, prefix) +
           encode(row + half, column + half, half, prefix) + ")";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> prefix(n + 1, vector<int>(n + 1));
    for (int row = 1; row <= n; ++row) {
        string pixels;
        cin >> pixels;
        for (int column = 1; column <= n; ++column) {
            prefix[row][column] = pixels[column - 1] - '0' +
                                  prefix[row - 1][column] +
                                  prefix[row][column - 1] -
                                  prefix[row - 1][column - 1];
        }
    }

    cout << encode(0, 0, n, prefix) << '\n';
}
