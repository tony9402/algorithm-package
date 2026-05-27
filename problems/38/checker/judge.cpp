#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    setName("compare output token by token");
    registerTestlibCmd(argc, argv);

    int tokens = 0;
    while (!ans.seekEof()) {
        string expected = ans.readToken();
        if (ouf.seekEof()) {
            quitf(_wa, "missing token %d, expected '%s'", tokens + 1, compress(expected).c_str());
        }
        string actual = ouf.readToken();
        ++tokens;
        if (expected != actual) {
            quitf(_wa, "token %d differs - expected: '%s', found: '%s'",
                  tokens, compress(expected).c_str(), compress(actual).c_str());
        }
    }
    if (!ouf.seekEof()) {
        string extra = ouf.readToken();
        quitf(_wa, "extra output token after %d tokens: '%s'", tokens, compress(extra).c_str());
    }
    quitf(_ok, "%d tokens", tokens);
}
