# https://www.acmicpc.net/problem/1915

n, m = map(int, input().split())

# 패딩을 이용하여 i-1행과 j-1열이 음수가 되지 않도록 한다.
dp = [[0]*(m+1)] + [[0]*(m+1) for _ in range(n)]
arr = ['0'*(m+1)] + ['0' + input() for _ in range(n)]

res = 0
for i in range(1,n+1):
    for j in range(1, m+1):
        len = min(dp[i-1][j], dp[i][j-1])
        if arr[i][j] == '0': continue

        dp[i][j] = len + (1 if arr[i-len][j-len] == '1' else 0)
        res = max(res, dp[i][j]*dp[i][j])
print(res)