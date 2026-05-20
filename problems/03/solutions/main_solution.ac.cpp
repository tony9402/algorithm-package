#include<iostream>
#include<vector>
#include<utility>
#include<queue>
#include<tuple>
#include<algorithm>

using namespace std;

int Map[25][25], temperature[25][25], N, M, K;
vector<pair<int, int>> heater[4];
vector<pair<int, int>> checkpoint;

// UDLR -> 0123
// 오왼위아래
const int U = 2, D = 3, L = 1, R = 0;
const int dy[] = {0,0,-1,1};
const int dx[] = {1,-1,0,0};
const int rev[] = { L, R, D, U }; // RLUD -> LRDU
const pair<int, int> dir[][3] = {
    {{-1, 1},{ 0, 1},{ 1, 1}}, // R
    {{-1,-1},{ 0,-1},{ 1,-1}}, // L
    {{-1,-1},{-1, 0},{-1, 1}}, // U
    {{ 1,-1},{ 1, 0},{ 1, 1}}  // D
};
const int dd[4][3] = { {U,0,D}, {U,0,D},{L,0,R},{L,0,R} };

bool inrange(int y, int x) { return 0 <= y && y < N && 0 <= x && x < M; }

void wind() {
    int dis[25][25] = {}, used[25][25] = {}, cnt = 0;
    for(int d = 0; d < 4; d++) {
        for(auto [y, x] : heater[d]) {
            ++cnt;
            queue<tuple<int, int, int>> Q;
            if(Map[y][x] & (1 << d)) continue;
            y += dy[d]; x += dx[d];
            if(!inrange(y, x)) continue;
            Q.emplace(y, x, 5);
            used[y][x] = cnt;
            while(!Q.empty()) {
                auto [y, x, kk] = Q.front(); Q.pop();
                dis[y][x] += kk;
                if(kk == 1) continue;
                for(int k = 0; k < 3; k++) {
                    int qy = y + dir[d][k].first;
                    int qx = x + dir[d][k].second;
                    if(!inrange(qy, qx)) continue;
                    if(used[qy][qx] == cnt) continue;
                    if(Map[qy][qx] & (1 << rev[d])) continue;
                    if(k != 1 && Map[y][x] & (1 << dd[d][k])) continue;
                    used[qy][qx] = cnt;
                    Q.emplace(qy, qx, kk - 1);
                }
            }
        }
    }
    for(int i = 0; i < N; i++) for(int j = 0; j < M; j++) temperature[i][j] += dis[i][j];
}

void control() {
    int tmp[25][25] = {};
    for(int i = 0; i < N; i++) {
        for(int j = 1; j < M; j++) {
            if(Map[i][j] & (1 << L)) continue;
            int d = abs(temperature[i][j - 1] - temperature[i][j]) / 4;
            if(temperature[i][j - 1] < temperature[i][j]) {
                tmp[i][j] -= d;
                tmp[i][j - 1] += d;
            }
            else {
                tmp[i][j] += d;
                tmp[i][j - 1] -= d;
            }
        }
    }
    for(int i = 1; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(Map[i][j] & (1 << U)) continue;
            int d = abs(temperature[i - 1][j] - temperature[i][j]) / 4;
            if(temperature[i - 1][j] < temperature[i][j]) {
                tmp[i][j] -= d;
                tmp[i - 1][j] += d;
            }
            else {
                tmp[i][j] += d;
                tmp[i - 1][j] -= d;
            }
        }
    }
    for(int i = 0; i < N; i++) for(int j = 0; j < M; j++) temperature[i][j] += tmp[i][j];
}

void down() {
    int tmp[25][25] = { };
    for(int i = 0; i < N; i++) tmp[i][0] = tmp[i][M - 1] = -1;
    for(int j = 0; j < M; j++) tmp[0][j] = tmp[N - 1][j] = -1;
    for(int i = 0; i < N; i++) for(int j = 0; j < M; j++) {
        if(temperature[i][j] == 0) continue;
        temperature[i][j] += tmp[i][j];
    }
}

bool check() {
    for(auto [y, x] : checkpoint) {
        if(temperature[y][x] < K) return false;
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M >> K;
    for(int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int x; cin >> x;
            if(1 <= x && x <= 4) heater[x - 1].emplace_back(i, j);
            else if(x == 5) checkpoint.emplace_back(i, j);
        }
    }
    int Q; cin >> Q;
    while(Q--) {
        int y, x, d; cin >> y >> x >> d;
        y--; x--;
        if(d==0) {
            Map[y][x] |= (1 << U);
            if(y) Map[y - 1][x] |= (1 << D);
        }
        else {
            Map[y][x] |= (1 << R);
            if(x + 1 < M) Map[y][x + 1] |= (1 << L);
        }
    }

    int ans = 0;
    while(true) {
        wind();
        control();
        down();
        ans++;
        if(check()) break;
        if(ans > 100) break;
    }
    if(ans > 100) ans = 101;
    cout << ans;

    return 0;
}