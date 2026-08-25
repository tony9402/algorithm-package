# https://www.acmicpc.net/problem/2110

import sys

def input():
    return sys.stdin.readline()

def determine(house, c, x):
    prev = house[0]
    router = 1
    for h in house:
        if router ==  c:
            return True
        if h - prev >= x:
            router += 1
            prev = h

    return router == c

def parametric_search(house, c):
    start = 1
    end = 0x3f3f3f3f
    while start < end:
        mid = (start + end) // 2

        if determine(house, c, mid):
            start = mid + 1
        else:
            end = mid
    return start - 1


n, c = map(int, sys.stdin.readline().split())
house = []
for i in range(n):
    house.append(int(sys.stdin.readline()))
house.sort()

print(parametric_search(house, c))
