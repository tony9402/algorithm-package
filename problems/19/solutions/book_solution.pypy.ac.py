import sys

input = sys.stdin.readline

n = int(input())
original = []
for _ in range(n):
    row = list(map(int, input().split()))
    mask = 0
    for col, value in enumerate(row):
        if value:
            mask |= 1 << col
    original.append(mask)

limit = (1 << n) - 1


def same_row(mask):
    return (mask ^ ((mask << 1) & limit) ^ (mask >> 1)) & limit


answer = n * n + 1
for first in range(1 << n):
    board = original[:]
    count = first.bit_count()

    board[0] ^= same_row(first)
    if n > 1:
        board[1] ^= first

    for row in range(1, n):
        press = board[row - 1]
        count += press.bit_count()
        board[row - 1] ^= press
        board[row] ^= same_row(press)
        if row + 1 < n:
            board[row + 1] ^= press

    if board[n - 1] == 0 and count < answer:
        answer = count

print(-1 if answer == n * n + 1 else answer)
