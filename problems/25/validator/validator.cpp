#include "testlib.h"

using namespace std;

const int MAX = 1 << 28;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    int N = inf.readInt(1, 4000);
    inf.readEoln();
    
    for(int i = 0; i < N; ++i) {
        int a = inf.readInt(-MAX, MAX); inf.readSpace();
        int b = inf.readInt(-MAX, MAX); inf.readSpace();
        int c = inf.readInt(-MAX, MAX); inf.readSpace();
        int d = inf.readInt(-MAX, MAX);
        inf.readEoln();
    }
    inf.readEof();
    
    return 0;
}
