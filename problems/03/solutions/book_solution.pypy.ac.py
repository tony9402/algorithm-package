# https://www.acmicpc.net/problem/23289 * 삼성전자 기출문제 *

from collections import deque

offset = 0
conv = [0,1,3,0,2]
dr = [-1,0,1,0]
dc = [0,1,0,-1]

def is_end(temperature, chocolate, check):
    ok = 0
    for r, c in check:
        ok += 1 if temperature[r][c] >= k else 0
    return ok == len(check) or chocolate > 100

def cold(temperature):
    n, m = len(temperature), len(temperature[0])

    for i in range(n):
        if temperature[i][-1]: temperature[i][-1] -= 1
        if temperature[i][0]: temperature[i][0] -= 1

    for j in range(1, m-1):
        if temperature[0][j]: temperature[0][j] -= 1
        if temperature[-1][j]: temperature[-1][j] -= 1

def adjust_temp(temperature, wall):
    n = len(temperature)
    m = len(temperature[0])
    diff = [[0]*m for _ in range(n)]

    for r in range(n):
        for c in range(m):
            for d in range(4):
                if wall[r][c] & (1<<d): continue
                nr, nc = r + dr[d], c + dc[d]
                if temperature[r][c] > temperature[nr][nc]:
                    v = (temperature[r][c] - temperature[nr][nc]) // 4
                    diff[nr][nc] += v
                    diff[r][c] -= v
    
    for r in range(n):
        for c in range(m):
            temperature[r][c] += diff[r][c]

def hot_wind(temperature, wall, heater, visit):
    global offset
    offset += 1
    r, c, d = heater

    q = deque([(r, c, 5)])

    visit[r][c] = offset

    while q:
        r, c, t = q.popleft()
        if t == 0: continue

        temperature[r][c] += t

        if (wall[r][c] & (1 << d)) == 0:
            nr, nc = r + dr[d], c + dc[d]
            if visit[nr][nc] != offset:
                visit[nr][nc] = offset
                q.append((nr, nc, t-1))

        for nextd in [(d+3)%4, (d+1)%4]:
            if wall[r][c] & (1 << nextd): continue
            nr = r + dr[nextd]
            nc = c + dc[nextd]

            if wall[nr][nc] & (1 << d): continue
            nnr = nr + dr[d]
            nnc = nc + dc[d]
            if visit[nnr][nnc] != offset:
                visit[nnr][nnc] = offset
                q.append((nnr, nnc, t-1))

def simulate(temperature, heaters, wall, visit):
    for heater in heaters:
        hot_wind(temperature,wall, heater, visit)
    adjust_temp(temperature, wall)
    cold(temperature)

n, m, k = map(int, input().split())
wall = [[0]*(m) for _ in range(n)]

heaters = []
check = []
temperature = [[0]*m for _ in range(n)]

#map init
for j in range(m):
    wall[0][j] |= 1
    wall[-1][j] |= 4
for i in range(n):
    wall[i][0] |= 8 
    wall[i][-1] |= 2

# room passing
room = [list(map(int, input().split())) for _ in range(n)]
for i in range(n):
    for j, v in enumerate(room[i]):
        # 조사 대상 칸 좌표 수집
        if v == 5:
            check.append((i,j))
        # 온풍기 좌표 수집
        elif v != 0:
            d = conv[v]
            heaters.append((i + dr[d], j + dc[d], d))

# 0: 상 1 : 우
for i in range(int(input())):
    r, c, d = map(int,input().split())
    r -= 1
    c -= 1
    if d == 0:
        wall[r][c] |= 1
        wall[r-1][c] |= 4
    else:
        wall[r][c] |= 2
        wall[r][c+1] |= 8

visit = [[0]*m for _ in range(n)]
chocolate = 0

while not is_end(temperature, chocolate, check):
    simulate(temperature, heaters, wall, visit)
    chocolate += 1

print(chocolate)
