# https://www.acmicpc.net/problem/13549

from collections import deque

N, K = map(int, input().split())

# 도착한 지점이 없으므로 매우 큰 값을 초기에 할당
t = [0x3f3f3f3f] * 100001

dq = deque([N])

t[N] = 0

# 조건을 deque나 리스트를 넣으면, 자료 구조에 데이터가 있을 경우 True
while dq:
    now = dq.popleft()
    # 순간이동
    if now*2 < len(t) and t[now*2] > t[now]:
        t[now*2] = t[now]
        dq.append(now*2)

    # 이동
    for move in [1,-1]:
        next = now + move
        if 0 <= next < len(t) and t[next] > t[now]+1:
            t[next] = t[now]+1
            dq.append(next)

print(t[K])
