#include "testlib.h"

using namespace std;

const int MAX = 300000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int R = inf.readInt(1, 500); inf.readSpace();
    int C = inf.readInt(1, 500);
    inf.readEoln();

    vector<int> check(MAX + 1);
    for(int i = 0; i < R; ++i) {
        for(int j = 0; j < C; ++j) {
            int x = inf.readInt(0, MAX);
            if(j + 1 != C) inf.readSpace();
            ensuref(check[x] == 0, "Find Duplication");
            check[x] = 1;
        }
        inf.readEoln();
    }
    inf.readEof();

    return 0;
}
