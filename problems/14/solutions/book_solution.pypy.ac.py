# https://www.acmicpc.net/problem/17069

n = int(input())

house = []
for i in range(n):
    house.append(list(map(int, input().split())))

# 다음 파이프의 위치
di = [0,1,1]
dj = [1,0,1]

# 0 = 가로, 1 = 세로, 2 = 대각선
# 빈공간 체크
# 가로는 오른쪽 한 칸만 빈 공간이면 됩니다.
# 세로는 아래 한 칸만 빈 공간이면 됩니다.
# 대각선 아래는 오른쪽, 아래 오른쪽 아래 대각선 칸이 빈 공간이어야 합니다.
check_i = [[0],[1],[0,1,1]]
check_j = [[1],[0],[1,0,1]]

# 가로 파이프는 대각선 방향과 가로 방향 파이프를 이어서 놓을 수 있습니다.
# 세로 파이프는 대각선 방향과 세로 방향 파이프를 이어서 놓을 수 있습니다.
# 대각선 파이프는 대각선 방향과 세로 방향, 가로 방향 파이프를 모두 놓을 수 있습니다.
next_pipe = [[0,2], [1,2], [0,1,2]]

def valid_pipe(house, i, j, p):
    for di, dj in zip(check_i[p], check_j[p]):
        ci = i + di
        cj = j + dj
        if not (0 <= ci < n and 0 <= cj < n) or house[ci][cj] == 1: return False
    return True

pipe = [[[0]*n for _ in range(n)] for _ in range(3)]
pipe[0][0][1] = 1

for i in range(n):
    for j in range(n):
        if house[i][j] == 1: continue
        for p in range(3):
            for np in next_pipe[p]:
                if valid_pipe(house, i, j, np):
                    ni = i + di[np]
                    nj = j + dj[np]
                    pipe[np][ni][nj] += pipe[p][i][j]
print(pipe[0][-1][-1] + pipe[1][-1][-1] + pipe[2][-1][-1])
