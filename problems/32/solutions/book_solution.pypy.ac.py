# https://www.acmicpc.net/problem/1516

from collections import deque

n = int(input())

adj = [[] for _ in range(n)]
# 건설에 필요한 최소 시간
build_time = [0] * n
# 진입 차수
indegree = [0] * n
need_time = [0] * n
q = deque()

for i in range(n):
    info = list(map(int, input().split()))
    # 정보의 0번은 건물을 짓는 시간, 마지막은 -1이므로 진입 차수는 (info의 길이 -2) 입니다.
    indegree[i] = len(info) - 2
    need_time[i] = info[0]

    for need in info[1:-1]:
        # 건물 번호 0번부터 시작합니다.
        adj[need - 1].append(i)

for building in range(n):
    # 진입 차수 0인 노드를 큐에 삽입합니다.
    if indegree[building] == 0:
        q.append(building)
        # 처음 건물들의 건축 완성 시간은 건물을 건설하는데 걸리는 시간과 일치합니다.
        build_time[building] = need_time[building]

while q:
    constructed = q.popleft()

    for next in adj[constructed]:
        # 다음 건물의 완성 시간은 이전 건물이 완성된 시간에
        # 해당 건물의 건설 시간을 더한 값들 중 최댓값이 됩니다.
        build_time[next] = max(build_time[next], build_time[constructed] + need_time[next])

        indegree[next] -= 1
        if indegree[next] == 0:
            q.append(next)

# 정답 출력
for t in build_time:
    print(t)
