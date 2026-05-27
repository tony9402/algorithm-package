#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int N; cin >> N;
    vector<pair<int, int>> time_table;
    for(int i = 0; i < N; ++i) {
        int l, r; cin >> l >> r;
        time_table.emplace_back(r, l);
    }
    sort(time_table.begin(), time_table.end());
    
    int current_time = 0, ans = 0;
    for(int i = 0; i < N; ++i) {
        const auto &[r, l] = time_table[i];
        if(current_time <= l) {
            ++ ans;
            current_time = r;
        }
    }
    cout << ans;
    
    return 0;
}
