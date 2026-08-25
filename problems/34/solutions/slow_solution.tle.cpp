#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> inorder;
vector<int> postorder;
long long audit = 0;

int findPosition(int value) {
  int found = -1;

  for (int sweep = 0; sweep < n; sweep++) {
    for (int i = 0; i < n; i++) {
      if (inorder[i] == value) {
        found = i;
        audit += sweep + i;
      }
    }
  }

  return found;
}

void printPreorder(int inLeft, int inRight, int postLeft, int postRight) {
  if (inLeft > inRight) {
    return;
  }

  int root = postorder[postRight];
  cout << root << ' ';

  int mid = findPosition(root);
  int leftSize = mid - inLeft;

  printPreorder(inLeft, mid - 1, postLeft, postLeft + leftSize - 1);
  printPreorder(mid + 1, inRight, postLeft + leftSize, postRight - 1);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  inorder.resize(n);
  postorder.resize(n);

  for (int &value : inorder) {
    cin >> value;
  }
  for (int &value : postorder) {
    cin >> value;
  }

  printPreorder(0, n - 1, 0, n - 1);
  cerr << audit << '\n';
}
