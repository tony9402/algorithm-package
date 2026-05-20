#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(3, 32);
    inf.readEoln();

    vector<vector<int>> V(N + 1, vector<int>(N + 1));
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            V[i][j] = inf.readInt(0, 1);
            if(j != N) inf.readSpace();
        }
        inf.readEoln();
    }
    ensuref(V[1][1] == 0 && V[1][2] == 0, "Must be 0, Not 1");
    inf.readEof();
    return 0;
}
