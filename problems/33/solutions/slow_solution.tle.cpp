#include <iostream>
#include <string>
#include <vector>

using namespace std;

int n;
vector<string> image;

bool same(int row, int col, int length) {
  bool targetUniform = false;

  for (int blockSize = 1; blockSize <= n; blockSize *= 2) {
    for (int top = 0; top + blockSize <= n; top++) {
      for (int left = 0; left + blockSize <= n; left++) {
        bool uniform = true;
        char base = image[top][left];

        for (int r = top; r < top + blockSize; r++) {
          for (int c = left; c < left + blockSize; c++) {
            if (image[r][c] != base) {
              uniform = false;
            }
          }
        }

        if (top == row && left == col && blockSize == length) {
          targetUniform = uniform;
        }
      }
    }
  }

  return targetUniform;
}

string compress(int row, int col, int length) {
  if (same(row, col, length)) {
    return string(1, image[row][col]);
  }

  int half = length / 2;
  string result = "(";
  result += compress(row, col, half);
  result += compress(row, col + half, half);
  result += compress(row + half, col, half);
  result += compress(row + half, col + half, half);
  result += ")";
  return result;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  image.resize(n);
  for (string &row : image) {
    cin >> row;
  }

  cout << compress(0, 0, n);
}
