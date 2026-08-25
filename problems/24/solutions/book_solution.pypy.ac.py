import sys

input = sys.stdin.readline

n, d, k, c = map(int, input().split())
sushi = [int(input()) for _ in range(n)]

counts = [0] * (d + 1)
kinds = 0

for i in range(k):
    plate = sushi[i]
    if counts[plate] == 0:
        kinds += 1
    counts[plate] += 1

answer = kinds if counts[c] else kinds + 1
right = k

for left in range(n):
    remove = sushi[left]
    counts[remove] -= 1
    if counts[remove] == 0:
        kinds -= 1

    add = sushi[right % n]
    if counts[add] == 0:
        kinds += 1
    counts[add] += 1

    candidate = kinds if counts[c] else kinds + 1
    if candidate > answer:
        answer = candidate

    right = (right + 1) % n

print(answer)
