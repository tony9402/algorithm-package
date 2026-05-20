#include<iostream>
#include<queue>

using namespace std;

const int dr[4] = {-1, 0, 1, 0};
const int dc[4] = {0, 1, 0, -1};

int N, M;
// 방문을 int 형식으로 관리 (바이러스의 조합을 할 때마다 visited 초기화 방지)
vector<vector<int>> visited;
vector<vector<int>> arr;
vector<pair<int, int>> virus;

int area;
int v;

int bfs() {
    queue<pair<int, int>> Q;

    for(const auto &[r, c]: virus) {
        Q.emplace(r, c);
        visited[r][c] = v;
    }

    int t = 0;
    int notEmpty = 0;

    while(!Q.empty()) {
        int count = (int)Q.size();

        // 조건문이 int 타입일 경우 int가 0이면 False, 이외에는 True
        while(count) {
            -- count;
            auto [r, c] = Q.front(); Q.pop();
            notEmpty += arr[r][c] == 0 ? 1 : 0;
            for(int d = 0; d < 4; ++d) {
                int nr = r + dr[d], nc = c + dc[d];
                if(!(0 <= nr && nr < N && 0 <= nc && nc < N) || visited[nr][nc] == v) continue;
                if(arr[nr][nc] == 1) continue;
                visited[nr][nc] = v;
                Q.emplace(nr, nc);
            }
        }

        // 빈칸이 모두 사라지면 반복문 탈출
        if(area == notEmpty) break;
        ++ t;
    }
    return area == notEmpty ? t : 0x3f3f3f3f;
}

int dfs(int r, int c) {
    // base case
    if((int)virus.size() == M) {
        ++ v;
        return bfs();
    }
    if(r == N) {
        return 0x3f3f3f3f;
    }

    // 다음 좌표 계산
    int nr = c + 1 == N ? r + 1 : r;
    int nc = c + 1 == N ? 0 : c + 1;
    int ret = 0x3f3f3f3f;

    if(arr[r][c] == 2) {
        virus.emplace_back(r, c);
        ret = dfs(nr, nc);
        virus.pop_back();
    }

    return min(ret, dfs(nr, nc));
}

int main() {
    // 빠른 입출력을 위해 사용합니다.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    visited.resize(N, vector<int>(N));
    arr.resize(N, vector<int>(N));

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> arr[i][j];
            // 삼항 연산자를 이용하여 빈 공간만 확인
            area += arr[i][j] == 0 ? 1 : 0;
        }
    }

    int ret = dfs(0, 0);
    cout << (ret != 0x3f3f3f3f ? ret : -1) << '\n';
    return 0;
}