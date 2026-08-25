# https://www.acmicpc.net/problem/11404

n = int(input())
m = int(input())

INF = 100 * 100000

cost = [[INF] * (n+1) for _ in range(n+1)]

for city in range(1, n+1):
    cost[city][city] = 0

for _ in range(m):
    a, b, c = map(int, input().split())
    cost[a][b] = min(cost[a][b], c)

for mid in range(1, n+1):
    for start in range(1, n+1):
        for end in range(1, n+1):
            cost[start][end] = min(cost[start][mid] + cost[mid][end], cost[start][end])

for start in range(1, n+1):
    for end in range(1, n+1):
        if cost[start][end] == INF:
            c = 0
        else:
            c = cost[start][end]
        print(c, end=' ')
    print()
