import sys
input = sys.stdin.readline
dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]
def solution(map, virus):
    n = len(map)
    visited = [[False] * n for _ in range(n)]
    time = 0
    count = 0
    while virus:
        curr = virus.popleft()
        # v의 인접한 위치를 감염시킨다.
        x, y = curr[0], curr[1]
        visited[x][y] = True
        for i in range(4):
            # 이동가능하면서 빈칸이면
            if 0 <= x + dx[i] < n and 0 <= y + dy[i] < n and not visited[x + dx[i]][y + dy[i]]:
                # 빈칸이면
                if map[x + dx[i]][y + dy[i]] == 0:
                    map[x + dx[i]][y + dy[i]] = map[x][y] + 1
                    time = max(time, map[x][y] + 1)
                    visited[x + dx[i]][y + dy[i]] = True
                    # 해당좌표를 큐에 넣는다.
                    virus.append((x + dx[i], y + dy[i]))
                    count += 1
    if count < empty:
        return -1
        # 최소시간을 리턴한다.
    return time


from collections import deque
from itertools import combinations
n, m = map(int, input().split())
graph = []
global empty
empty = 0
virus_all = []
for i in range(n):
    temp = list(map(int, input().split()))
    for j in range(n):
        if temp[j] == 2:
            temp[j] = 0
            virus_all.append((i, j))
        elif temp[j] == 0:
            empty += 1
    graph.append(temp)

import copy
answer = 2500
for case in combinations(virus_all, m):
    virus = deque()
    graph_ = copy.deepcopy(graph)
    for c in case:
        virus.append(c)
        graph_[c[0]][c[1]] = 0
    s = solution(graph_, virus)
    if s == -1:
        continue
    answer = min(answer, s)
if answer == 2500:
    print(-1)
else:
    print(answer)