#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> population(n);
    for (int &value : population) {
        cin >> value;
    }
    vector<int> adjacent(n);
    for (int i = 0; i < n; ++i) {
        int count;
        cin >> count;
        while (count-- > 0) {
            int neighbor;
            cin >> neighbor;
            adjacent[i] |= 1 << (neighbor - 1);
        }
    }

    int full = (1 << n) - 1;
    vector<char> connected(full + 1);
    vector<int> sum(full + 1);
    for (int mask = 1; mask <= full; ++mask) {
        int bit = mask & -mask;
        int node = __builtin_ctz(static_cast<unsigned>(bit));
        sum[mask] = sum[mask ^ bit] + population[node];
        if ((mask & (mask - 1)) == 0) {
            connected[mask] = true;
            continue;
        }
        for (int candidate = mask; candidate != 0; candidate &= candidate - 1) {
            int vertex_bit = candidate & -candidate;
            int vertex = __builtin_ctz(static_cast<unsigned>(vertex_bit));
            int rest = mask ^ vertex_bit;
            if (connected[rest] && (adjacent[vertex] & rest) != 0) {
                connected[mask] = true;
                break;
            }
        }
    }

    int answer = INT_MAX;
    for (int first = 1; first < full; ++first) {
        if ((first & 1) == 0) {
            continue;
        }
        int second = full ^ first;
        if (connected[first] && connected[second]) {
            int difference = sum[first] - sum[second];
            if (difference < 0) {
                difference = -difference;
            }
            answer = min(answer, difference);
        }
    }

    cout << (answer == INT_MAX ? -1 : answer) << '\n';
    return 0;
}
