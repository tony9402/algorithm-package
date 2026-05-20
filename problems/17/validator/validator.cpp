#include "testlib.h"

using namespace std;

const int MAX = 2147483647;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100000);
    inf.readEoln();

    for(int i = 0; i < N; ++i) {
        int l = inf.readInt(0, MAX); inf.readSpace();
        int r = inf.readInt(l, MAX);
        inf.readEoln();
    }
    inf.readEof();

    return 0;
}
