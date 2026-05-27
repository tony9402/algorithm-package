#include "testlib.h"
#include <iostream>

using namespace std;

void Print(int C, const vector<int> &V) {
    int N = (int)V.size();
    cout << N << ' ' << C << '\n';
    for(int i = 0; i < N; ++i) cout << V[i] << '\n';
}

void random_generate(int N, int C, int min_value = 0, int max_value = 1'000'000'000) {
    set<int> st;
    while(st.size() < N) st.insert(rnd.next(min_value, max_value));
    vector<int> V(st.begin(), st.end());
    shuffle(V.begin(), V.end());
    Print(C, V);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int minN = opt<int>("minN", 2);
    int maxN = opt<int>("maxN", 200000);
    int minC = opt<int>("minC", 2);
    int minV = opt<int>("minV", 0);
    int maxV = opt<int>("maxV", 1'000'000'000);
    string mode = opt<string>("mode", "random");
    
    int N = rnd.next(minN, maxN);
    N = min(N, maxV - minV + 1);
    int C = rnd.next(2, N);
    if(mode == "random") {
        random_generate(N, C, minV, maxV);
    }
    
    return 0;
}
