#include "testlib.h"
#include <vector>
#include <stack>
#include <functional>
#include <algorithm>
 
using namespace std;
 
#define MAXN 200000
 
int main(int argc, char **argv) {
    registerValidation(argc, argv);
 
    int N = inf.readInt(1, MAXN, "N");
    inf.readEoln();
    vector<int> color(N + 1);
    vector<vector<int>> graph(N + 1);
    for(int i = 1; i <= N; i++) {
        color[i] = inf.readInt(0, N, "Color");
        if(i == N) inf.readEoln();
        else inf.readSpace();
    }
    for(int i = 0; i + 1 < N; i++) {
        int a = inf.readInt(1, N, "u"); inf.readSpace();
        int b = inf.readInt(1, N, "v"); inf.readEoln();
        ensure(a != b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    
    // validate
    stack<int> st;
    vector<int> pre(N + 1);
    vector<int> dfs_color(N + 1);
    st.push(1);
    
    while(!st.empty()) {
        int cur = st.top(); st.pop();
        int prev = pre[cur];
        int c = dfs_color[cur];
        
        if(c) ensure(color[cur] != 0);
        int flag = dfs_color[cur] | color[cur];
        for(int nxt: graph[cur]) {
            if(nxt == prev) continue;
            pre[nxt] = cur;
            dfs_color[nxt] |= flag;
            st.push(nxt);
        }
    }

    inf.readEof();
}
