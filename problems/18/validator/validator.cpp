#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    int N = inf.readInt(0, 10000);
    inf.readEoln();
    
    for(int i = 0; i < N; ++i) {
        int p = inf.readInt(1, 10000); inf.readSpace();
        int d = inf.readInt(1, 10000);
        inf.readEoln();
    }
    inf.readEof();

    return 0;
}
