#include<iostream>
#include<vector>

using namespace std;

int N, M;
// 이미 선택된 수인지 체크
vector<int> visited;
vector<int> res;

void permutation(int len) {
    // 현재 선택된 배열의 길이
    // base case: 배열이 처음에 주어진 m만큼 선택
    if(len == M) {
        for(int i: res) {
            cout << i << ' ';
        }
        cout << '\n';
        return;
    }
    for(int i = 0; i < N; ++i) {
        // 1 ~ n 까지의 수 선택
        int v = i + 1;

        // 이미 선택된 수면 다른 수 선택
        if(visited[v] == 1)
            continue;
        visited[v] = 1;
        res.push_back(v);

        // 다음 수 선택
        permutation(len+1);

        // 이전에 선택된 수 체크 해재 후 선택된 수를 배열에서 제거
        visited[v] = 0;
        res.pop_back();
    }
}

int main() {
    // 빠른 입출력을 위해 사용합니다.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    visited.resize(N + 1);
    permutation(0);

    return 0;
}
