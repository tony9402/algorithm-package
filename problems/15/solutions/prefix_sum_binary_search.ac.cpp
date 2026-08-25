#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int rows, columns;
    cin >> rows >> columns;
    vector<vector<int>> prefix(rows + 1, vector<int>(columns + 1));
    for (int row = 1; row <= rows; ++row) {
        string line;
        cin >> line;
        for (int column = 1; column <= columns; ++column) {
            prefix[row][column] = prefix[row - 1][column] + prefix[row][column - 1]
                - prefix[row - 1][column - 1] + (line[column - 1] - '0');
        }
    }

    int low = 0;
    int high = min(rows, columns) + 1;
    while (low + 1 < high) {
        const int length = (low + high) / 2;
        bool found = false;
        for (int row = length; row <= rows && !found; ++row) {
            for (int column = length; column <= columns; ++column) {
                const int ones = prefix[row][column] - prefix[row - length][column]
                    - prefix[row][column - length] + prefix[row - length][column - length];
                if (ones == length * length) {
                    found = true;
                    break;
                }
            }
        }
        if (found) low = length;
        else high = length;
    }

    cout << low * low << '\n';
    return 0;
}
