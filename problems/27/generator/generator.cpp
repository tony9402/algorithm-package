#include "testlib.h"
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

char label(int x) {
  if (x == -1) {
    return '.';
  }
  return char('A' + x - 1);
}

void print_tree(int n, const vector<pair<int, int>> &child) {
  cout << n << '\n';
  for (int i = 1; i <= n; ++i)
    cout << label(i) << ' ' << label(child[i].first) << ' '
         << label(child[i].second) << '\n';
}

void attach_child(vector<pair<int, int>> &child, int parent, int node) {
  bool left_free = child[parent].first == -1;
  bool right_free = child[parent].second == -1;
  if (left_free && right_free) {
    if (rnd.next(0, 1))
      child[parent].first = node;
    else
      child[parent].second = node;
  } else if (left_free) {
    child[parent].first = node;
  } else {
    child[parent].second = node;
  }
}

bool has_slot(const vector<pair<int, int>> &child, int node) {
  return child[node].first == -1 || child[node].second == -1;
}

void generate_random(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<pair<int, int>> child(n + 1, {-1, -1});
  vector<int> available = {1};
  for (int node = 2; node <= n; ++node) {
    int idx = rnd.next(0, (int)available.size() - 1);
    int parent = available[idx];
    attach_child(child, parent, node);
    if (!has_slot(child, parent))
      available.erase(available.begin() + idx);
    available.push_back(node);
  }
  print_tree(n, child);
}

void generate_random_pq(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<pair<int, int>> child(n + 1, {-1, -1});
  priority_queue<pair<int, int>> pq;
  pq.emplace(rnd.next(1, 100000), 1);
  for (int node = 2; node <= n; ++node) {
    while (!pq.empty() && !has_slot(child, pq.top().second))
      pq.pop();
    int parent = pq.top().second;
    pq.pop();
    attach_child(child, parent, node);
    if (has_slot(child, parent))
      pq.emplace(rnd.next(1, 100000), parent);
    pq.emplace(rnd.next(1, 100000), node);
  }
  print_tree(n, child);
}

void generate_left_chain(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<pair<int, int>> child(n + 1, {-1, -1});
  for (int node = 1; node < n; ++node)
    child[node].first = node + 1;
  print_tree(n, child);
}

void generate_right_chain(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<pair<int, int>> child(n + 1, {-1, -1});
  for (int node = 1; node < n; ++node)
    child[node].second = node + 1;
  print_tree(n, child);
}

void generate_balanced(int minN, int maxN) {
  int n = rnd.next(minN, maxN);
  vector<pair<int, int>> child(n + 1, {-1, -1});
  for (int node = 2; node <= n; ++node) {
    int parent = node / 2;
    if (node % 2 == 0)
      child[parent].first = node;
    else
      child[parent].second = node;
  }
  print_tree(n, child);
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  int minN = opt<int>("minN", 1);
  int maxN = opt<int>("maxN", 26);
  string mode = opt<string>("mode", "random");

  if (mode == "random")
    generate_random(minN, maxN);
  else if (mode == "random_pq")
    generate_random_pq(minN, maxN);
  else if (mode == "left_chain")
    generate_left_chain(minN, maxN);
  else if (mode == "right_chain")
    generate_right_chain(minN, maxN);
  else if (mode == "balanced")
    generate_balanced(minN, maxN);
  else {
    cerr << "unknown mode: " << mode << '\n';
    return 1;
  }
  return 0;
}
