#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    int N = inf.readInt(1, 26);
    inf.readEoln();
    
    vector<int> uf(N + 1, -1), size(N + 1, 1);
    function<int(int)> find = [&](int x) -> int {
        return uf[x] < 0 ? x : uf[x] = find(uf[x]);
    };
    function<bool(int, int)> merge = [&](int u, int v) -> bool {
        u = find(u); v = find(v);
        if(u == v) return false;
        uf[v] = u;
        size[u] += size[v];
        return true;
    };
    
    string regex = "[.A-" + format("%c", (char)('A' + N - 1)) + "]{1,1}";
    
    for(int i = 0; i < N; ++i) {
        string cur_s = inf.readToken(regex.c_str()); inf.readSpace();
        string left_s = inf.readToken(regex.c_str()); inf.readSpace();
        string right_s = inf.readToken(regex.c_str());
        inf.readEoln();
        
        int cur = cur_s[0] - 'A' + 1;
        int l = left_s[0] == '.' ? -1 : left_s[0] - 'A' + 1;
        int r = right_s[0] == '.' ? -1 : right_s[0] - 'A' + 1;
        
        if(l != -1) merge(cur, l);
        if(r != -1) merge(cur, r);
    }
    
    ensuref(size[find(1)] == N, "This is not a tree");
    inf.readEof();
    
    return 0;
}
