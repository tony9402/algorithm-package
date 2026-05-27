#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    int N = inf.readInt(2, 3'000'000); inf.readSpace();
    int d = inf.readInt(2, 3'000); inf.readSpace();
    int k = inf.readInt(2, 3'000); inf.readSpace();
    int c = inf.readInt(1, d);
    inf.readEoln();
    
    for(int i = 0; i < N; ++i) {
        int x = inf.readInt(1, d);
        inf.readEoln();
    }

    inf.readEof();
    
    return 0;
}
