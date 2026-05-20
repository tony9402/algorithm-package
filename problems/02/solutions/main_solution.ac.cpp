#include<iostream>
#include<vector>

using namespace std;

const int dr[4] = {-1, 0, 1, 0};
const int dc[4] = {0, 1, 0, -1};
int N, M;
int room[50][50];
int clean;

bool is_wall(int r, int c) {
    return room[r][c] == 1;
}

void clean_room(int r, int c) {
    room[r][c] = 2;
}

int get_next_dir(int r, int c, int dir) {
    for(int d = 1; d < 5; ++d) {
        int nd = ((dir - d) % 4 + 4) % 4;
        int nr = r + dr[nd];
        int nc = c + dc[nd];
        if(0 <= nr && nr < N && 0 <= nc && nc < M) {
            if(room[nr][nc] == 0) {
                return nd;
            }
        }
    }
    return -404 + (dir + 2) % 4;
}

int main() {
    // 빠른 입출력을 위해 사용됩니다.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    int r, c, dir; cin >> r >> c >> dir;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            cin >> room[i][j];
        }
    }

    while(!is_wall(r, c)) {
        clean += (int)(room[r][c] == 0);
        clean_room(r, c);
        int next_dir = get_next_dir(r, c, dir);

        if(next_dir >= 0) dir = next_dir;
        else next_dir += 404;
        r += dr[next_dir];
        c += dc[next_dir];
    }

    cout << clean;

    return 0;
}