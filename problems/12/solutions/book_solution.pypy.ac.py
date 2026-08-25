# https://www.acmicpc.net/problem/2579

n = int(input())
stair = []

for num in range(n):
    stair.append(int(input()))

# 2. Bottom Up
score = [[0]*max(2,n) for _ in range(3)]
score[1][0] = stair[0]
score[2][0] = -0x3f3f3f3f

# 중요: 계단이 1칸만 있는 경우에는 stair[1]에서 indexError 발생
if n > 1:
    score[2][1] = stair[1]
    score[1][1] = stair[0] + stair[1]

for i in range(2, n):
    score[1][i] = stair[i] + score[2][i-1]
    score[2][i] = stair[i] + max(score[1][i-2], score[2][i-2])

print(max(score[1][n-1], score[2][n-1]))
