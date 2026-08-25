# https://www.acmicpc.net/problem/2252

from collections import deque

n, m = map(int, input().split())
indegree = [0] * (n+1)
adj = [[] for _ in range(n+1)]
q = deque()

for i in range(m):
    front, rear = map(int, input().split())
    # 앞사람 다음에 뒷사람이 오도록 간선을 추가합니다.
    adj[front].append(rear)
    # 뒷사람의 진입 차수를 증가시킵니다.
    indegree[rear] += 1

for i in range(1, n+1):
    # 진입 차수가 0인 노드들을 큐에 삽입합니다.
    if indegree[i] == 0:
        q.append(i)

while q:
    student = q.popleft()
    # 처리된 학생은 바로 출력합니다.
    print(student, end=' ')

    for next in adj[student]:
        # 처리된 학생과 인접한 학생들의 진입 차수를 1 감소시킵니다.
        # 이후에 앞에 있어야하는 학생이 없다면 처리 가능하므로 큐에 삽입합니다.
        indegree[next] -= 1
        if indegree[next] == 0:
            q.append(next)
