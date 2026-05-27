#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();
    for (int tc = 0; tc < t; ++tc) {
        int n = inf.readInt(1, 1000, "n");
        inf.readEoln();
        for (int i = 0; i < n; ++i) {
            inf.readToken("[UDFBLR][+-]", "move");
            if (i + 1 == n) inf.readEoln();
            else inf.readSpace();
        }
    }
    inf.readEof();
    return 0;
}
