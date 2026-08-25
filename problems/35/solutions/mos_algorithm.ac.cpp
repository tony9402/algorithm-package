#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

struct Query {
    int left;
    int right;
    int index;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int& number : numbers) {
        cin >> number;
    }

    int query_count;
    cin >> query_count;
    vector<Query> queries(query_count);
    for (int i = 0; i < query_count; ++i) {
        cin >> queries[i].left >> queries[i].right;
        --queries[i].left;
        --queries[i].right;
        queries[i].index = i;
    }

    int block_size = max(1, static_cast<int>(sqrt(n)));
    sort(queries.begin(), queries.end(), [block_size](const Query& a,
                                                       const Query& b) {
        int a_block = a.left / block_size;
        int b_block = b.left / block_size;
        if (a_block != b_block) {
            return a_block < b_block;
        }
        if (a_block % 2 == 0) {
            return a.right < b.right;
        }
        return a.right > b.right;
    });

    vector<long long> answers(query_count);
    int current_left = 0;
    int current_right = -1;
    long long sum = 0;
    for (const Query& query : queries) {
        while (current_left > query.left) {
            sum += numbers[--current_left];
        }
        while (current_right < query.right) {
            sum += numbers[++current_right];
        }
        while (current_left < query.left) {
            sum -= numbers[current_left++];
        }
        while (current_right > query.right) {
            sum -= numbers[current_right--];
        }
        answers[query.index] = sum;
    }

    for (long long answer : answers) {
        cout << answer << '\n';
    }
}
