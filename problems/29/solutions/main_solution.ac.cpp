#include<iostream>
#include<vector>
#include<functional>
#include<algorithm>
 
using namespace std;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
 
    int N; cin >> N;
    vector<int> color(N + 1);
    for(int i = 1; i <= N; i++) cin >> color[i];
    vector<vector<int>> graph(N + 1);
    vector<int> par(N + 1);
    for(int i = 1; i < N; i++) {
        int a, b; cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    function<void(int, int)> dfs = [&](int cur, int prev) -> void {
        par[cur] = prev;
        for(int nxt : graph[cur]) {
            if(nxt == prev) continue;
            dfs(nxt, cur);
        }
    };
    dfs(1, 0);
    int answer = 0;
    for(int i = 1; i <= N; i++) answer += (color[i] != color[par[i]]);
    cout << answer;
 
    return 0;
}
