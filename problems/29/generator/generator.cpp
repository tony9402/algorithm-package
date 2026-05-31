#include "testlib.h"
#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;

void Print(
    int N, 
    const vector<int> &color,
    const vector<pair<int, int>> &edges
) {
    cout << N << '\n';
    for(int i = 1; i <= N; ++i) {
        cout << color[i];
        if(i == N) cout << '\n';
        else cout << ' ';
    }
    int M = (int)edges.size();
    for(int i = 0; i < M; ++i) {
        int u = edges[i].first;
        int v = edges[i].second;
        cout << u << ' ' << v << '\n';
    }
}

vector<int> coloring(int N, const vector<pair<int, int>> &edges) {
    vector<vector<int>> tree(N + 1);
    int M = (int)edges.size();
    for(int i = 0; i < M; ++i) {
        int u = edges[i].first, v = edges[i].second;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    vector<int> color(N + 1);
    vector<int> pre(N + 1);
    vector<int> offset(N + 1);
    stack<int> st;
    st.push(1);
    
    while(!st.empty()) {
        int cur = st.top(); st.pop();
        if(rnd.next(0, 1)) color[cur] = rnd.next(offset[cur], N);
        else color[cur] = color[pre[cur]];
        for(int nxt: tree[cur]) {
            if(nxt == pre[cur]) continue;
            pre[nxt] = cur;
            offset[nxt] = !!color[cur];
            st.push(nxt);
        }
    }
    return color;
}

void random_skewed_generate(int N) {
    vector<int> nodes(N);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end());
    vector<pair<int, int>> edges;
    for(int i = 0; i + 1 < N; i++) {
        edges.emplace_back(nodes[i], nodes[i + 1]);
    }

    vector<int> color = coloring(N, edges);
    Print(N, color, edges);
}

void random_generate(int N) {
    vector<int> uf(N + 1, -1);
    function<int(int)> find = [&](int x) -> int { 
        return uf[x] < 0 ? x : uf[x] = find(uf[x]);
    };
    function<bool(int, int)> merge = [&](int u, int v) -> bool {
        u = find(u); v = find(v);
        if(u == v) return false;
        uf[v] = u;
        return true;
    };
    vector<pair<int, int>> edges;
    for(int i = 0; i < N - 1; i++) {
        int a = rnd.next(1, N);
        int b = rnd.next(1, N);
        while(find(a) == find(b)) b = rnd.next(1, N);
        merge(a, b);
        edges.emplace_back(a, b);
    }

    vector<int> color = coloring(N, edges);
    Print(N, color, edges);
}

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);

    int minN = opt<int>("minN", 1);
    int maxN = opt<int>("maxN", 200'000);
    string mode = opt<string>("mode", "random"); //ranodm, skewed

    int N = rnd.next(minN, maxN);
    if(mode == "random") {
        random_generate(N);
    }
    else if(mode == "skewed") {
        random_skewed_generate(N);
    }
}