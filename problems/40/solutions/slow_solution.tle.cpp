#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool startsWithSlow(const string &word, const string &query) {
  if (word.size() < query.size()) {
    return false;
  }

  for (size_t length = 1; length <= query.size(); length++) {
    string prefix;
    for (size_t i = 0; i < length; i++) {
      prefix.push_back(word[i]);
    }

    if (length == query.size() && prefix == query) {
      return true;
    }
  }

  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<string> words(n);
  for (string &word : words) {
    cin >> word;
  }

  int answer = 0;
  while (m--) {
    string query;
    cin >> query;

    bool found = false;
    for (const string &word : words) {
      if (startsWithSlow(word, query)) {
        found = true;
      }
    }

    if (found) {
      answer++;
    }
  }

  cout << answer;
}
