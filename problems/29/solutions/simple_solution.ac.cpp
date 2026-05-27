#include<iostream>
#include<vector>
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
    int answer = (color[0] != color[1]);
    for(int i = 1; i < N; i++) {
        int a, b; cin >> a >> b;
        answer += (color[a] != color[b]);
    }
    cout << answer;
    return 0;
}
