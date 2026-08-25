# https://www.acmicpc.net/problem/1389

from collections import deque

n, m = map(int, input().split())
adj = [[] for _ in range(n+1)]

for _ in range(m):
    a,b = map(int, input().split())
    adj[a].append(b)
    adj[b].append(a)

visit = [0]*(n+1)
dist = [0]*(n+1)

q = deque([])
answer = 0
min_kevin = 0x3f3f3f3f

#BFS를 통한 순회
for start in range(1, n+1):
    q.append(start)

    #방문 체크를 boolean으로 하지 않고 int 값으로 하여 초기화 하지 않도록 합니다
    visit[start] = start
    dist[start] = 0
    kevin = 0

    while q:
        now = q.popleft()

        for next in adj[now]:
            if visit[next] != start:
                dist[next] = dist[now]+1
                visit[next] = start
                kevin += dist[next]
                q.append(next)

    if min_kevin > kevin:
        min_kevin = kevin
        answer = start

print(answer)
