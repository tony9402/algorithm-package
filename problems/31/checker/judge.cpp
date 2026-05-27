#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    setName("check a valid topological ordering");
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<pair<int, int>> edges;
    edges.reserve(m);
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt();
        int b = inf.readInt();
        edges.emplace_back(a, b);
    }

    vector<int> pos(n + 1, -1);
    for (int i = 0; i < n; ++i) {
        if (ouf.seekEof()) {
            quitf(_wa, "output has only %d vertices, expected %d", i, n);
        }
        int v = ouf.readInt(1, n, "vertex");
        if (pos[v] != -1) {
            quitf(_wa, "vertex %d appears more than once", v);
        }
        pos[v] = i;
    }
    if (!ouf.seekEof()) {
        int extra = ouf.readInt();
        quitf(_wa, "extra output after %d vertices: %d", n, extra);
    }

    for (auto [a, b] : edges) {
        if (pos[a] >= pos[b]) {
            quitf(_wa, "constraint %d before %d is violated", a, b);
        }
    }
    quitf(_ok, "valid topological order");
}
