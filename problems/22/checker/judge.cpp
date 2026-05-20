#include "testlib.h"

using namespace std;

int main(int argc, char *argv[]) {
    setName("compare ordered sequences of signed int%d numbers", 8 * int(sizeof(long long)));
    registerTestlibCmd(argc, argv);

    int N = inf.readInt();
    int M = inf.readInt();
    vector<int> balls(N);
    for(int i = 0; i < N; ++i) balls[i] = inf.readInt();

    int n = 0;
    string firstElems;

    vector<int> user_output(M);

    long long first_answer = -1;
    long long total_cnt_by_user = 0, total_cnt_by_main_solution = 0;
    while (!ans.seekEof() && !ouf.seekEof()) {
        long long j = ans.readLong();
        long long p = ouf.readLong();
        if(n > 0) user_output[n - 1] = p;
        if(n == 0) first_answer = j;
        else {
            total_cnt_by_user += p;
            total_cnt_by_main_solution += j;
        }
        n++;
        if (j != p)
            quitf(_wa, "%d%s numbers differ - expected: '%s', found: '%s'", n, englishEnding(n).c_str(),
                  vtos(j).c_str(), vtos(p).c_str());
        else if (n <= 5) {
            if (firstElems.length() > 0)
                firstElems += " ";
            firstElems += vtos(j);
        }
    }

    int extraInAnsCount = 0;

    while (!ans.seekEof()) {
        ans.readLong();
        extraInAnsCount++;
    }

    int extraInOufCount = 0;

    while (!ouf.seekEof()) {
        ouf.readLong();
        extraInOufCount++;
    }

    if (extraInAnsCount > 0)
        quitf(_wa, "Answer contains longer sequence [length = %d], but output contains %d elements",
              n + extraInAnsCount, n);

    if (extraInOufCount > 0)
        quitf(_wa, "Output contains longer sequence [length = %d], but answer contains %d elements",
              n + extraInOufCount, n);

    /*
    스페셜 저지
    */
    vector<long long> psum(N + 1);
    for(int i = 1; i <= N; ++i) psum[i] = psum[i - 1] + balls[i - 1];
    if(total_cnt_by_user != N) quitf(_wa, "The total number is not correct (User Solution)");
    if(total_cnt_by_main_solution != N) quitf(_wa, "The total number is not correct (MCS)");

    int pre = 0;
    long long mx = 0;
    for(int i = 0; i < M; ++i) {
        long long cnt = user_output[i];
        long long sum = psum[pre + cnt] - psum[pre];
        if(sum > first_answer) quitf(_wa, "Wrong Divide %d > %d (%d)", sum, first_answer, i);
        pre += cnt;
    }

    if (n <= 5)
        quitf(_ok, "%d number(s): \"%s\"", n, compress(firstElems).c_str());
    else
        quitf(_ok, "%d numbers", n);
}