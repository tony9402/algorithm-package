# https://www.acmicpc.net/problem/24230
# 경인지역 6개대학 연합 shake! 2021 C번

import sys
input = sys.stdin.readline

sys.setrecursionlimit(10**6)
n = int(input())
color = [-1] + list(map(int, input().split()))
adj = [[] for _ in range(n+1)]

def send(node, p):
    # 하얀색이 아닌 색으로 칠해져있을 경우 색칠해야 합니다.
    num = 1 if color[node] != 0 else 0

    for child in adj[node]:
        # 자식 쪽으로 탐색을 진행합니다.
        if child == p: continue
        if color[node] != 0 and color[child] == color[node]:
            # 만약 자식 노드 색이 부모 노드 색과 동일하다면, 
            # 아래 부분 트리의 최솟값을 하나 줄입니다.
            num += send(child, node) - 1
        else:
            num += send(child, node)

    return num

for _ in range(n-1):
    a,b = map(int,input().split())
    adj[a].append(b)
    adj[b].append(a)

print(send(1, -1))