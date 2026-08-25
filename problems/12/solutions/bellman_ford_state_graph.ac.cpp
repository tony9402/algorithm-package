#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> score(n + 1);
    for (int stair = 1; stair <= n; ++stair) cin >> score[stair];

    const int UNREACHABLE = -1000000000;
    vector<array<int, 3>> distance(n + 1);
    for (auto &state : distance) state.fill(UNREACHABLE);
    distance[0][0] = 0;

    for (int iteration = 0; iteration < n; ++iteration) {
        for (int stair = n - 1; stair >= 0; --stair) {
            for (int consecutive = 0; consecutive <= 2; ++consecutive) {
                if (distance[stair][consecutive] == UNREACHABLE) continue;
                if (stair + 1 <= n && consecutive < 2) {
                    distance[stair + 1][consecutive + 1] = max(
                        distance[stair + 1][consecutive + 1],
                        distance[stair][consecutive] + score[stair + 1]
                    );
                }
                if (stair + 2 <= n) {
                    distance[stair + 2][1] = max(
                        distance[stair + 2][1],
                        distance[stair][consecutive] + score[stair + 2]
                    );
                }
            }
        }
    }

    cout << max(distance[n][1], distance[n][2]) << '\n';
    return 0;
}
