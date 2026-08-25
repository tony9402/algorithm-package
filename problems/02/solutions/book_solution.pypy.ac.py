# https://www.acmicpc.net/problem/14503 * 삼성전자 기출문제 *

# 상, 우, 하, 좌
dr = (-1,0,1,0)
dc = (0,1,0,-1)

N, M = map(int, input().split())
r, c, dir = map(int, input().split())
room = [list(map(int, input().split())) for _ in range(N)]

def is_wall(r,c):
    return room[r][c] == 1

def clean_room(r,c):
    room[r][c] = 2

def get_next_dir(r,c,dir):
    for d in range(1,5):
        nd = (dir - d) % 4
        nr, nc = r + dr[nd], c + dc[nd]
        if 0 <= nr < N and 0 <= nc < M:
            if room[nr][nc] == 0:
                return nd

    return -404 + (dir+2)%4

clean = 0

while not is_wall(r,c):
    if(room[r][c] == 0):
        clean += 1
    clean_room(r,c)
    next_dir = get_next_dir(r, c, dir)

    if next_dir >= 0:
        dir = next_dir
    else:
        next_dir += 404
    r, c = r + dr[next_dir], c + dc[next_dir]

print(clean)
