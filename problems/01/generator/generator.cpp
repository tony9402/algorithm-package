#include "testlib.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int DAYS[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool is_leap_year(int year) {
  return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

int calculate_checksum(int sum) {
  int normalized = ((1 - sum) % 11 + 11) % 11;
  return normalized;
}

vector<string> generate_codes(int n) {
  set<string> codes;
  while ((int)codes.size() < n) {
    codes.insert(rnd.next("[1-9]{1,1}[0-9]{5,5}"));
  }
  vector<string> result(codes.begin(), codes.end());
  shuffle(result.begin(), result.end());
  return result;
}

string generate_birth() {
  int year = rnd.next(1900, 2011);
  int month = rnd.next(1, 12);
  int extra_day = is_leap_year(year) && month == 2 ? 1 : 0;
  int day = rnd.next(1, DAYS[month] + extra_day);

  ostringstream out;
  out << setfill('0') << setw(4) << year << setw(2) << month << setw(2) << day;
  return out.str();
}

string generate_leap_day_birth() {
  vector<int> years;
  for (int year = 1900; year <= 2011; ++year) {
    if (is_leap_year(year))
      years.push_back(year);
  }
  int year = years[rnd.next(0, (int)years.size() - 1)];
  ostringstream out;
  out << setfill('0') << setw(4) << year << "0229";
  return out.str();
}

string sequence_code(bool male) {
  int code = rnd.next(1, 999);
  if (male)
    code |= 1;
  else
    code &= ~1;
  if (code == 0)
    code += 2;

  ostringstream out;
  out << setfill('0') << setw(3) << code;
  return out.str();
}

string build_valid_id(const string &code, const string &birth,
                      const string &seq_code) {
  string token = code + birth + seq_code;
  ensure(token.size() == 17);

  int sum = 0;
  for (int i = 0; i < 17; ++i) {
    int x = token[i] - '0';
    int w = 1 << (17 - i);
    sum = (sum + x * w % 11) % 11;
  }
  int checksum = calculate_checksum(sum);
  token.push_back(checksum == 10 ? 'X' : char('0' + checksum));
  ensure((sum + checksum) % 11 == 1);
  return token;
}

void print_case(const string &token, const vector<string> &codes) {
  cout << token << '\n';
  cout << codes.size() << '\n';
  for (const string &code : codes)
    cout << code << '\n';
}

void generate_random(int minN, int maxN) {
  string token = rnd.next("[0-9]{17,17}");
  token.push_back(rnd.next(0, 1) ? 'X' : rnd.next("[0-9]{1,1}")[0]);
  print_case(token, generate_codes(rnd.next(minN, maxN)));
}

void generate_no_random(bool male, int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<string> codes = generate_codes(n);
  string token = build_valid_id(codes[rnd.next(0, n - 1)], generate_birth(),
                                sequence_code(male));
  print_case(token, codes);
}

void generate_edgecase1(bool male, int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<string> codes = generate_codes(n);
  string token = build_valid_id(codes[rnd.next(0, n - 1)],
                                generate_leap_day_birth(), sequence_code(male));
  print_case(token, codes);
}

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 1);
  int maxN = opt<int>("maxN", 50);
  bool male = opt<bool>("male", true);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN);
  else if (mode == "no_random")
    generate_no_random(male, minN, maxN);
  else if (mode == "edgecase1")
    generate_edgecase1(male, minN, maxN);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
