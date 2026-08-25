#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int word_count, query_count;
    cin >> word_count >> query_count;
    vector<string> words(word_count);
    vector<string> queries(query_count);
    for (string& word : words) {
        cin >> word;
    }
    for (string& query : queries) {
        cin >> query;
    }
    sort(words.begin(), words.end());
    sort(queries.begin(), queries.end());

    int answer = 0;
    int word_index = 0;
    for (const string& query : queries) {
        while (word_index < word_count && words[word_index] < query) {
            ++word_index;
        }
        if (word_index < word_count &&
            words[word_index].compare(0, query.size(), query) == 0) {
            ++answer;
        }
    }
    cout << answer << '\n';
}
