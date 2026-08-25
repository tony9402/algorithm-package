#include "testlib.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string random_move() {
  static const string faces = "UDFBLR";
  string move;
  move.push_back(faces[rnd.next(0, (int)faces.size() - 1)]);
  move.push_back(rnd.next(0, 1) ? '+' : '-');
  return move;
}

void print_moves(const vector<string> &moves) {
  cout << moves.size() << '\n';
  for (int i = 0; i < (int)moves.size(); ++i) {
    if (i)
      cout << ' ';
    cout << moves[i];
  }
  cout << '\n';
}

void generate_random(int minT, int maxT, int minN, int maxN) {
  int t = rnd.next(minT, maxT);
  cout << t << '\n';
  for (int tc = 0; tc < t; ++tc) {
    int n = rnd.next(minN, maxN);

    vector<string> moves;
    moves.reserve(n);
    for (int i = 0; i < n; ++i)
      moves.push_back(random_move());
    print_moves(moves);
  }
}

void generate_same_face(int minT, int maxT, int minN, int maxN) {
  int t = rnd.next(minT, maxT);
  cout << t << '\n';
  for (int tc = 0; tc < t; ++tc) {
    int n = rnd.next(minN, maxN);
    static const string faces = "UDFBLR";
    char face = faces[rnd.next(0, (int)faces.size() - 1)];

    vector<string> moves;
    moves.reserve(n);
    for (int i = 0; i < n; ++i) {
      string move;
      move.push_back(face);
      move.push_back(rnd.next(0, 1) ? '+' : '-');
      moves.push_back(move);
    }
    print_moves(moves);
  }
}

void generate_inverse_pairs(int minT, int maxT, int minN, int maxN) {
  int t = rnd.next(minT, maxT);
  cout << t << '\n';
  for (int tc = 0; tc < t; ++tc) {
    int n = rnd.next(minN, maxN);
    n += n % 2;

    vector<string> moves;
    moves.reserve(n);
    for (int i = 0; i < n; i += 2) {
      string move = random_move();
      moves.push_back(move);
      move[1] = move[1] == '+' ? '-' : '+';
      moves.push_back(move);
    }
    print_moves(moves);
  }
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minT = opt<int>("minT", 1);
  int maxT = opt<int>("maxT", 20);
  int minN = opt<int>("minN", 1);
  int maxN = opt<int>("maxN", 1000);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minT, maxT, minN, maxN);
  else if (mode == "same_face")
    generate_same_face(minT, maxT, minN, maxN);
  else if (mode == "inverse_pairs")
    generate_inverse_pairs(minT, maxT, minN, maxN);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
