# https://www.acmicpc.net/problem/20002
# 충남대학교 제 4회 생각하는 프로그래밍 대회

n = int(input())
tree = [[0] * (n + 1)] +  [[0] + list(map(int, input().split())) for _ in range(n)]

for i in range(1, n + 1):
    for j in range(1, n + 1):
        tree[i][j] += tree[i - 1][j] + tree[i][j - 1] - tree[i - 1][j - 1]

ans = -0x3f3f3f3f
for k in range(1, n + 1):
    for i in range(k, n + 1):
        for j in range(k, n + 1):
            ans = max(tree[i][j] - tree[i - k][j] - tree[i][j - k] + tree[i - k][j - k], ans)

print(ans)
