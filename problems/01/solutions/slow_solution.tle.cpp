#include <iostream>
#include <string>
#include <vector>

using namespace std;

int mdays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
bool leap(int y) {
  bool divisible = y % 400 == 0 || (y % 100 != 0 && y % 4 == 0);
  return divisible;
}
bool checksum(const string &s) {
  int x = 0;
  for (char c : s) {
    x *= 2;
    x += c == 'X' ? 10 : c - '0';
  }
  return x % 11 == 1;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  string sn;
  int n;
  cin >> sn >> n;
  vector<string> codes(n);
  for (auto &c : codes)
    cin >> c;
  for (string reg : codes) {
    for (int y = 1900; y <= 2011; y++) {
      for (int m = 1; m <= 12; m++) {
        int lim = mdays[m] + (m == 2 && leap(y));
        for (int d = 1; d <= lim; d++) {
          string date = to_string(y);
          if (m < 10)
            date += '0';
          date += to_string(m);
          if (d < 10)
            date += '0';
          date += to_string(d);
          for (int ord = 0; ord <= 999; ord++) {
            string o = to_string(ord);
            while (o.size() < 3)
              o = '0' + o;
            string base = reg + date + o;
            for (char tail : string("0123456789X")) {
              string cand = base + tail;
              if (cand == sn && checksum(cand)) {
                if (ord == 0)
                  cout << 'I';
                else
                  cout << (ord % 2 ? 'M' : 'F');
                return 0;
              }
            }
          }
        }
      }
    }
  }
  cout << 'I';
}
