#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

bool getBit(const vector<uint64_t> &bits, int index) {
    return (bits[index / 64] >> (index % 64)) & 1ULL;
}

void flipBit(vector<uint64_t> &bits, int index) {
    bits[index / 64] ^= 1ULL << (index % 64);
}

int bitCount(const vector<uint64_t> &bits) {
    int result = 0;
    for (uint64_t block : bits) result += __builtin_popcountll(block);
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    const int variables = n * n;
    const int equationBlocks = (variables + 1 + 63) / 64;
    vector<vector<uint64_t>> matrix(variables, vector<uint64_t>(equationBlocks));
    const int dr[] = {0, -1, 0, 1, 0};
    const int dc[] = {0, 0, 1, 0, -1};

    for (int row = 0; row < n; ++row) {
        for (int column = 0; column < n; ++column) {
            const int equation = row * n + column;
            for (int direction = 0; direction < 5; ++direction) {
                const int pressRow = row + dr[direction];
                const int pressColumn = column + dc[direction];
                if (pressRow < 0 || pressRow >= n || pressColumn < 0 || pressColumn >= n) continue;
                flipBit(matrix[equation], pressRow * n + pressColumn);
            }
            int light;
            cin >> light;
            if (light) flipBit(matrix[equation], variables);
        }
    }

    vector<int> pivotRow(variables, -1);
    int rank = 0;
    for (int column = 0; column < variables; ++column) {
        int selected = rank;
        while (selected < variables && !getBit(matrix[selected], column)) ++selected;
        if (selected == variables) continue;
        swap(matrix[rank], matrix[selected]);
        pivotRow[column] = rank;
        for (int row = 0; row < variables; ++row) {
            if (row == rank || !getBit(matrix[row], column)) continue;
            for (int block = 0; block < equationBlocks; ++block) {
                matrix[row][block] ^= matrix[rank][block];
            }
        }
        ++rank;
    }

    for (int row = rank; row < variables; ++row) {
        bool hasCoefficient = false;
        for (int column = 0; column < variables; ++column) {
            if (getBit(matrix[row], column)) {
                hasCoefficient = true;
                break;
            }
        }
        if (!hasCoefficient && getBit(matrix[row], variables)) {
            cout << -1 << '\n';
            return 0;
        }
    }

    const int solutionBlocks = (variables + 63) / 64;
    vector<uint64_t> solution(solutionBlocks);
    for (int column = 0; column < variables; ++column) {
        if (pivotRow[column] != -1 && getBit(matrix[pivotRow[column]], variables)) {
            flipBit(solution, column);
        }
    }

    vector<vector<uint64_t>> basis;
    for (int freeColumn = 0; freeColumn < variables; ++freeColumn) {
        if (pivotRow[freeColumn] != -1) continue;
        vector<uint64_t> vector(solutionBlocks);
        flipBit(vector, freeColumn);
        for (int column = 0; column < variables; ++column) {
            if (pivotRow[column] != -1 && getBit(matrix[pivotRow[column]], freeColumn)) {
                flipBit(vector, column);
            }
        }
        basis.push_back(vector);
    }

    int answer = bitCount(solution);
    const unsigned long long combinations = 1ULL << basis.size();
    unsigned long long previousGray = 0;
    for (unsigned long long mask = 1; mask < combinations; ++mask) {
        const unsigned long long gray = mask ^ (mask >> 1);
        const unsigned long long changed = gray ^ previousGray;
        const int basisIndex = __builtin_ctzll(changed);
        for (int block = 0; block < solutionBlocks; ++block) {
            solution[block] ^= basis[basisIndex][block];
        }
        answer = min(answer, bitCount(solution));
        previousGray = gray;
    }

    cout << answer << '\n';
    return 0;
}
