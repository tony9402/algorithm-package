# https://www.acmicpc.net/problem/11657

n, m = map(int, input().split())
INF = 500 * 6000 * 10000

edges = []
arrival_time = [INF] * (n + 1)
arrival_time[1] = 0

for _ in range(m):
    a, b, c = map(int, input().split())
    edges.append((a, b, c))

infinite_time_travel = False

for count in range(n):
    for a, b, time in edges:
        if arrival_time[a] == INF: continue
        if arrival_time[a] + time < arrival_time[b]:
            if count == n - 1:
                infinite_time_travel = True

            arrival_time[b] = arrival_time[a] + time

if infinite_time_travel:
    print(-1)
else:
    for city in range(2, n+1):
        if arrival_time[city] == INF:
            print(-1)
        else:
            print(arrival_time[city])
