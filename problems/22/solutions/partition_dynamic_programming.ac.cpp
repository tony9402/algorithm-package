#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, group_count;
    cin >> n >> group_count;
    vector<int> bead(n), prefix(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> bead[i];
        prefix[i + 1] = prefix[i] + bead[i];
    }

    const int infinity = 1'000'000'000;
    vector<vector<int>> dp(group_count + 1, vector<int>(n + 1, infinity));
    dp[0][0] = 0;
    for (int groups = 1; groups <= group_count; ++groups) {
        for (int end = groups; end <= n; ++end) {
            for (int cut = groups - 1; cut < end; ++cut) {
                dp[groups][end] = min(
                    dp[groups][end],
                    max(dp[groups - 1][cut], prefix[end] - prefix[cut])
                );
            }
        }
    }

    int limit = dp[group_count][n];
    cout << limit << '\n';
    vector<int> sizes;
    int sum = 0;
    int size = 0;
    int made = 1;
    for (int i = 0; i < n; ++i) {
        if (sum + bead[i] > limit || n - i == group_count - made) {
            sizes.push_back(size);
            ++made;
            sum = bead[i];
            size = 1;
        } else {
            sum += bead[i];
            ++size;
        }
    }
    sizes.push_back(size);
    for (int count : sizes) {
        cout << count << ' ';
    }
    cout << '\n';
    return 0;
}
