#include <iostream>
#include <array>
#include <functional>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int N; cin >> N;
    vector<array<int, 2>> tree(27);
    
    function<int(char)> conv = [&](char ch) -> int {
        if(ch == '.') return -1;
        return ch - 'A' + 1;
    };
    function<char(int)> iconv = [&](int x) -> char {
        if(x == -1) return '.';
        return (char)(x + 'A' - 1);
    };
    for(int i = 1; i <= N; ++i) {
        char ch, lc, rc; cin >> ch >> lc >> rc;
        int cur = conv(ch);
        int l = conv(lc);
        int r = conv(rc);
        tree[cur][0] = l;
        tree[cur][1] = r;
    }
    
    // 전위순회
    function<void(int)> pre_order = [&](int root) -> void {
        if(root == -1) return;
        cout << iconv(root);
        pre_order(tree[root][0]);
        pre_order(tree[root][1]);
    };
    // 중위순회
    function<void(int)> in_order = [&](int root) -> void {
        if(root == -1) return;
        in_order(tree[root][0]);
        cout << iconv(root);
        in_order(tree[root][1]);
    };
    // 후위순회
    function<void(int)> post_order = [&](int root) -> void {
        if(root == -1) return;
        post_order(tree[root][0]);
        post_order(tree[root][1]);
        cout << iconv(root);
    };
    
    pre_order(conv('A'));
    cout << '\n';
    in_order(conv('A'));
    cout << '\n';
    post_order(conv('A'));

    return 0;
}
