#include "testlib.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string randomMove() {
    static const string faces = "UDFBLR";
    string move;
    move.push_back(faces[rnd.next(0, (int)faces.size() - 1)]);
    move.push_back(rnd.next(0, 1) ? '+' : '-');
    return move;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int minT = opt<int>("minT", 1);
    int maxT = opt<int>("maxT", 20);
    int minN = opt<int>("minN", 1);
    int maxN = opt<int>("maxN", 1000);
    string mode = opt<string>("mode", "random");

    int t = rnd.next(minT, maxT);
    cout << t << '\n';
    for (int tc = 0; tc < t; ++tc) {
        vector<string> moves;
        int n = rnd.next(minN, maxN);
        if (mode == "inverse_pairs") n += n % 2;
        moves.reserve(n);

        if (mode == "same_face") {
            static const string faces = "UDFBLR";
            char face = faces[rnd.next(0, (int)faces.size() - 1)];
            for (int i = 0; i < n; ++i) {
                string move;
                move.push_back(face);
                move.push_back(rnd.next(0, 1) ? '+' : '-');
                moves.push_back(move);
            }
        } else if (mode == "inverse_pairs") {
            for (int i = 0; i < n; i += 2) {
                string move = randomMove();
                moves.push_back(move);
                move[1] = move[1] == '+' ? '-' : '+';
                moves.push_back(move);
            }
        } else {
            for (int i = 0; i < n; ++i) moves.push_back(randomMove());
        }

        cout << moves.size() << '\n';
        for (int i = 0; i < (int)moves.size(); ++i) {
            if (i) cout << ' ';
            cout << moves[i];
        }
        cout << '\n';
    }
    return 0;
}
