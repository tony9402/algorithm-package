#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, 200000); inf.readSpace();
    int C = inf.readInt(2, N);
    inf.readEoln();

    set<int> st;
    for(int i = 0; i < N; ++i) {
        int x = inf.readInt(0, 1'000'000'000);
        inf.readEoln();
        st.insert(x);
    }
    ensuref(st.size() == N, "Detect Duplication");

    inf.readEof();
    return 0;
}
