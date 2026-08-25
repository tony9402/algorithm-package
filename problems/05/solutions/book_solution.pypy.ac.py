# https://www.acmicpc.net/problem/1260

from collections import deque

n, m, v = map(int, input().split())

# 인접 리스트 생성
adj = [[] for _ in range(n+1)]
# DFS와 BFS 중복 방문을 막기 위한 visit 배열 생성
visit = [0] * (n+1)

# 인접 리스트 생성
for i in range(m):
    f, t = map(int, input().split())
    adj[f].append(t)
    adj[t].append(f)

# 낮은 번호부터 방문하기 위해 정렬
for i in range(n):
    adj[i+1].sort()

def dfs(now):
    visit[now] = 1

    # 현재 방문한 지점 출력
    print(now, end=' ')

    # general case: 아직 방문하지 않은 지점 방문
    for next in adj[now]:
        if visit[next] == 1: continue
        dfs(next)

    # base case: 인접 행렬에서 다음에 방문할 노드가 없는 경우
    return

def bfs():
    q = deque([v])

    # DFS에서 방문 체크를 1로 했기 때문에, BFS는 2로 방문 체크
    visit[v] = 2

    while len(q) != 0:
        now = q.popleft()

        # 현재 방문한 지점 출력
        print(now, end=' ')

        for next in adj[now]:
            if visit[next] == 2: continue
            visit[next] = 2
            q.append(next)

# DFS 방문 지점 출력 후 BFS 방문 지점 출력
dfs(v)
print()
bfs()
