#include "testlib.h"
#include <iostream>
#include <set>

using namespace std;

int main(int argc, char** argv) {
    registerValidation(argc, argv);

    string token = inf.readToken("[0-9]{17}[0-9X]{1}");
    inf.readEoln();

    int N = inf.readInt(1, 50);
    inf.readEoln();

    set<string> codes;
    for(int i = 0; i < N; ++i) {
        string code = inf.readToken("[1-9][0-9]{5}");
        codes.insert(code);
        inf.readEoln();
    }
    ensure((int)codes.size() == N);
    inf.readEof();

    return 0;
}
