import sys

input = sys.stdin.readline

n = int(input())
graph = [[] for _ in range(n + 1)]

for _ in range(n - 1):
    a, b = map(int, input().split())
    graph[a].append(b)
    graph[b].append(a)

parent = [0] * (n + 1)
order = []
stack = [1]
parent[1] = -1

while stack:
    node = stack.pop()
    order.append(node)
    for next_node in graph[node]:
        if next_node == parent[node]:
            continue
        parent[next_node] = node
        stack.append(next_node)

dp0 = [0] * (n + 1)
dp1 = [0] * (n + 1)

for node in reversed(order):
    dp0[node] = 0
    dp1[node] = 1
    for next_node in graph[node]:
        if next_node == parent[node]:
            continue
        dp0[node] += dp1[next_node]
        dp1[node] += min(dp0[next_node], dp1[next_node])

print(min(dp0[1], dp1[1]))
