#include "testlib.h"
#include <vector>
#include <tuple>
#include <utility>
#include <algorithm>
#include <functional>

using namespace std;

// 오른쪽, 왼쪽, 위, 아래
const int dx[] = {0, 0, -1, 1};
const int dy[] = {1, -1, 0, 0};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int R = inf.readInt(2, 20); inf.readSpace();
    int C = inf.readInt(2, 20); inf.readSpace();
    int K = inf.readInt(1, 1000);
    inf.readEoln();

    vector<tuple<int, int, int>> heaters;
    
    int check5 = 0;
    for(int i = 1; i <= R; ++i) {
        for(int j = 1; j <= C; ++j) {
            int x = inf.readInt(0, 5);
            if(j != C) inf.readSpace();

            // 0: 빈 칸
            if(x == 0) { ; }
            // 5: 조사해야하는 칸
            else if(x == 5) ++ check5;
            // 1: 방향이 오른쪽인 온풍기가 있음
            // 2: 방향이 왼쪽인 온풍기가 있음
            // 3: 방향이 위인 온풍기가 있음
            // 4: 방향이 아래인 온풍기가 있음
            else {
                heaters.emplace_back(i, j, x);
            }
        }
        inf.readEoln();
    }
    int W = inf.readInt(0, R * C);
    inf.readEoln();
    vector<vector<pair<int, int>>> walls(2);
    vector<vector<int>> check_wall(R + 1, vector<int>(C + 1));
    for(int i = 0; i < W; ++i) {
        int x = inf.readInt(1, R); inf.readSpace();
        int y = inf.readInt(1, C); inf.readSpace();
        int t = inf.readInt(0, 1); inf.readEoln();
        int value = check_wall[x][y] >> t & 1;
        ensure(value == 0);
        check_wall[x][y] |= 1 << t;

        if(t == 0) ensuref(1 < x && x <= R, "Must be x > 1");
        else if(t == 1) ensuref(1 <= y && y < C, "Must be y < C");
        walls[t].emplace_back(x, y);
    }

    sort(walls[0].begin(), walls[0].end()); // 위, 아래
    sort(walls[1].begin(), walls[1].end()); // 오른쪽, 왼쪽

    function<bool(int, int)> is_in_range = [&](int x, int y) -> bool {
        return 1 <= x && x <= R && 1 <= y && y <= C;
    };

    for(const auto &[x, y, d]: heaters) {
        int nd = d - 1;
        ensure(is_in_range(x + dx[nd], y + dy[nd]));
        int rx = x + (dx[nd] < 0 ? 0 : dx[nd]);
        int ry = y + (dy[nd] > 0 ? 0 : dy[nd]);
        if(nd < 2) { // 오른쪽, 왼쪽
            ensure(!binary_search(walls[1].begin(), walls[1].end(), make_pair(rx, ry)));
        }
        else { // 위, 아래
            ensure(!binary_search(walls[0].begin(), walls[0].end(), make_pair(rx, ry)));
        }
    }
    inf.readEof();

    return 0;
}
