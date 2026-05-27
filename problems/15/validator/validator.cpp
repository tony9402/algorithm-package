#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    int N = inf.readInt(1, 1000); inf.readSpace();
    int M = inf.readInt(1, 1000);
    inf.readEoln();
    
    for(int i = 0; i < N; ++i) {
        string token = inf.readToken("[0-1]+");
        string message = "len(token) must be " + to_string(M) + "but, " + to_string((int)token.size());
        ensuref(token.size() == M, message.c_str());
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
