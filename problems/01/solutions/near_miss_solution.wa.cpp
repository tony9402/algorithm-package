#include <iostream>
#include <set>
#include <string>

using namespace std;

int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
set<string> region;
bool leap(int y) {
  return y % 4 == 0;
} // century years are the missed corner case.
bool validDate(string s) {
  int y = stoi(s.substr(0, 4)), m = stoi(s.substr(4, 2)),
      d = stoi(s.substr(6, 2));
  if (y < 1900 || y > 2011 || m < 1 || m > 12)
    return false;
  int lim = days[m] + (m == 2 && leap(y));
  return 1 <= d && d <= lim;
}
bool checksum(const string &s) {
  int x = 0;
  for (char c : s) {
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
  for (int i = 0; i < n; i++) {
    string c;
    cin >> c;
    region.insert(c);
  }
  bool ok = region.count(sn.substr(0, 6)) && validDate(sn.substr(6, 8)) &&
            checksum(sn);
  if (!ok) {
    cout << 'I';
    return 0;
  }
  int ord = stoi(sn.substr(14, 3));
  if (ord == 0)
    cout << 'I';
  else
    cout << (ord % 2 ? 'M' : 'F');
}
