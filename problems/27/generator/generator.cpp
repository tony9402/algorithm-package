#include "testlib.h"
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int get_weight(int lo = 1, int hi = 100000) {
    return rnd.next(lo, hi);
}

char conv(int x) {
    if(x == -1) return '.';
    return 'A' + x - 1;
}

void random_using_pq_generate(int N) {
    int root = 1;
    vector<int> nodes(N + 1);
    iota(nodes.begin(), nodes.end(), 0);
    if(N > 1) shuffle(nodes.begin() + 2, nodes.end());
    
    vector<pair<int, int>> edge(N + 1, make_pair(-1, -1)); // [left, right]
    priority_queue<pair<int, int>> pq;
    pq.emplace(get_weight(), root);
    
    int offset = 2;
    while(!pq.empty() && offset <= N) {
        auto [w, cur] = pq.top(); pq.pop();
        if(rnd.next(0, 1)) { // left
            edge[cur].first = nodes[offset];
            pq.emplace(get_weight(), nodes[offset]);
            ++ offset;
        }
        if(offset > N) break;
        if(rnd.next(0, 1)) { // right
            edge[cur].second = nodes[offset];
            pq.emplace(get_weight(), nodes[offset]);
            ++ offset;
        }
    }
    
    cout << N << '\n';
    for(int i = 1; i <= N; ++i) {
        cout << conv(i) << ' ' << conv(edge[i].first) << ' ' << conv(edge[i].second) << '\n';
    }
}

void random_generate(int N) {
    vector<int> parent(N + 1);
    int root = rnd.next(1, N);
    vector<vector<int>> groups(N + 1);
    set<int> st;
    for(int i = 1; i <= N; ++i) {
        groups[i].push_back(i);
        st.insert(i);
    }
    
    vector<int> uf(N + 1, -1), size(N + 1, 1);
    function<int(int)> find = [&](int x) -> int {
        return uf[x] < 0 ? x : uf[x] = find(uf[x]);
    };
    function<bool(int, int)> merge = [&](int u, int v) -> bool {
        u = find(u); v = find(v);
        if(u == v) return false;
        if(size[u] > size[v]) {
            while(!groups[v].empty()) {
                groups[u].push_back(groups[v].back());
                groups[v].pop_back();
            }
            uf[v] = u;
            size[u] += size[v];
        }
        else {
            while(!groups[u].empty()) {
                groups[v].push_back(groups[u].back());
                groups[u].pop_back();
            }
            uf[u] = v;
            size[v] += size[u];
        }
        return true;
    };
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int minN = opt<int>("minN", 1);
    int maxN = opt<int>("maxN", 1);
    string mode = opt<string>("mode", "random");
    
    int N = rnd.next(minN, maxN);
    if(mode == "random") {
        random_generate(N);
    }
    else if(mode == "random_pq") {
        random_using_pq_generate(N);
    }
    
    return 0;
}
