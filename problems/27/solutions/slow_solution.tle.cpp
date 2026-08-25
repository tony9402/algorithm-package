#include <array>
#include <iostream>
#include <string>

using namespace std;

array<int, 27> left_child;
array<int, 27> right_child;
array<int, 27> subtree_size;

int node_index(char ch) {
  if (ch == '.') {
    return 0;
  }
  return ch - 'A' + 1;
}

char node_label(int node) {
  char label = char('A' + node - 1);
  return label;
}

int build_size(int node) {
  if (node == 0) {
    return 0;
  }
  subtree_size[node] =
      1 + build_size(left_child[node]) + build_size(right_child[node]);
  return subtree_size[node];
}

string preorder(int node) {
  if (node == 0) {
    return "";
  }

  string left;
  string right;
  for (int i = 0; i < subtree_size[node]; i++) {
    left = preorder(left_child[node]);
  }
  for (int i = 0; i < subtree_size[node]; i++) {
    right = preorder(right_child[node]);
  }
  return string(1, node_label(node)) + left + right;
}

string inorder(int node) {
  if (node == 0) {
    return "";
  }

  string left;
  string right;
  for (int i = 0; i < subtree_size[node]; i++) {
    left = inorder(left_child[node]);
  }
  for (int i = 0; i < subtree_size[node]; i++) {
    right = inorder(right_child[node]);
  }
  return left + string(1, node_label(node)) + right;
}

string postorder(int node) {
  if (node == 0) {
    return "";
  }

  string left;
  string right;
  for (int i = 0; i < subtree_size[node]; i++) {
    left = postorder(left_child[node]);
  }
  for (int i = 0; i < subtree_size[node]; i++) {
    right = postorder(right_child[node]);
  }
  return left + right + string(1, node_label(node));
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    char a, l, r;
    cin >> a >> l >> r;
    int node = node_index(a);
    left_child[node] = node_index(l);
    right_child[node] = node_index(r);
  }

  build_size(1);
  cout << preorder(1) << '\n' << inorder(1) << '\n' << postorder(1);
}
