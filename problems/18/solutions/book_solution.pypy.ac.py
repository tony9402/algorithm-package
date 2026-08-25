import heapq
import sys

input = sys.stdin.readline

n = int(input())
lectures = []
for _ in range(n):
    pay, deadline = map(int, input().split())
    lectures.append((deadline, pay))
lectures.sort()

selected = []
for deadline, pay in lectures:
    heapq.heappush(selected, pay)
    if len(selected) > deadline:
        heapq.heappop(selected)

print(sum(selected))
