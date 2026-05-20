#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

// 인접 리스트 생성
vector<vector<int>> adj;
// DFS와 BFS 중복 방문을 막기 위한 visit 배열 생성
vector<int> visited;

void dfs(int now) {
    visited[now] = 1;
    // 현재 방문한 지점 출력
    cout << now << ' ';

    // general case: 아직 방문하지 않은 지점 방문
    for(int next: adj[now]) {
        if(visited[next] == 1) continue;
        dfs(next);
    }

    // base case: 인접 행렬에서 다음에 방문할 노드가 없는 경우
}

void bfs(int now) {
    queue<int> Q;
    Q.push(now);
    visited[now] = 2;

    while(!Q.empty()) {
        now = Q.front(); Q.pop();
        cout << now << ' ';
        for(int next: adj[now]) {
            if(visited[next] == 2) continue;
            visited[next] = 2;
            Q.push(next);
        }
    }
}


int main() {
    // 빠른 입출력을 위해 사용합니다.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, V;
    cin >> N >> M >> V;

    adj.resize(N + 1);
    visited.resize(N + 1);

    // 인접 리스트 생성
    for(int i = 0; i < M; ++i) {
        int f, t; cin >> f >> t;
        adj[f].push_back(t);
        adj[t].push_back(f);
    }

    // 낮은 번호부터 방문하기 위해 정렬
    for(int i = 0; i < N; ++i) {
        sort(adj[i + 1].begin(), adj[i + 1].end());
    }
    // DFS 방문 지점 출력 후 BFS 방문 지점 출력
    dfs(V);
    cout << '\n';
    bfs(V);

    return 0;
}