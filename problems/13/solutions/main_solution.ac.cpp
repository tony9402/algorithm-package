#include <iostream>
#include <vector>
#include <functional>

using namespace std;

const int dy[] = {-1,1,0,0,-1,-1,1,1};
const int dx[] = {0,0,-1,1,1,-1,1,-1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int R, C; cin >> R >> C;
    vector<vector<int>> V(R, vector<int>(C));

    function<bool(int, int)> is_in_range = [&](int y, int x) -> bool {
        return 0 <= y && y < R && 0 <= x && x < C;
    };

    int K = R * C;
    const int INF = 300001;
    vector<int> uf(K + 1, -1), size(K + 1, 1), minimum(K + 1, INF);

    for(int i = 0; i < R; ++i) {
        for(int j = 0; j < C; ++j) {
            cin >> V[i][j];
            int idx = i * C + j;
            minimum[idx] = V[i][j];
        }
    }

    function<int(int)> find = [&](int x) -> int {
        return uf[x] < 0 ? x : uf[x] = find(uf[x]);
    };
    function<bool(int, int)> merge = [&](int u, int v) -> bool {
        u = find(u); v = find(v);
        if(u == v) return false;
        if(minimum[u] > minimum[v]) swap(u, v);
        uf[v] = u;
        size[u] += size[v];
        return true;
    };

    for(int i = 0; i < R; ++i) {
        for(int j = 0; j < C; ++j) {
            int target = -1, current_min = V[i][j];
            for(int k = 0; k < 8; ++k) {
                int y = i + dy[k], x = j + dx[k];
                if(!is_in_range(y, x)) continue;
                if(current_min > V[y][x]) current_min = V[y][x], target = k;
            }
            if(target != -1) merge(i * C + j, (i + dy[target]) * C + (j + dx[target]));
        }
    }

    for(int i = 0; i < R; ++i) {
        for(int j = 0; j < C; ++j) {
            int x = i * C + j;
            if(find(x) == x) cout << size[x];
            else cout << 0;
            if(j + 1 != C) cout << ' ';
        }
        cout << '\n';
    }

    return 0;
}
