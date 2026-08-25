# https://www.acmicpc.net/problem/5373 * 삼성전자 기출문제 *

import sys 

color = 'wyrogb'
mapping = 'UDFBLR'

mapping_table = {c:i for i, c in enumerate(mapping)}
rotate_dir = {'-':3, '+':1}
rotate_table = [
    [36,37,38,18,19,20,45,46,47,27,28,29],
    [24,25,26,42,43,44,33,34,35,51,52,53],
    [6 ,7 ,8 ,44,41,38,11,10,9 ,45,48,51],
    [0 ,1 ,2 ,47,50,53,17,16,15,42,39,36],
    [6 ,3 ,0 ,29,32,35,15,12,9 ,24,21,18],
    [2 ,5 ,8 ,20,23,26,11,14,17,33,30,27]
]

# 큐브 한 면(3*3) 회전
def cw(cube):
    temp = [[0]*3 for _ in range(3)]

    for i in range (3):
        for j in range(3):
            temp[j][2-i] = cube[i][j]
    for i in range(3):
        cube[i][:] = temp[i][:]

def rotate_face(cube_flat, face):
    # 큐브 한 면(3*3) 회전
    # 면마다 9칸이 있으므로, cube_flat에 매핑할때에는 face*9를 더해준다.
    rotate_cube = [[cube_flat[i*3+j + face*9] for j in range(3)] for i in range(3)]

    cw(rotate_cube)

    # 다시 cube_flat으로 rotate_cube를 옮겨준다
    for i in range(3):
        for j in range(3):
            cube_flat[i*3 + j + face*9] = rotate_cube[i][j] 

def rotate_12(cube_flat, before_rotate_12, after_rotate_12):
    # 12칸 회전
    tmp = [cube_flat[v] for v in after_rotate_12] 
    for dst, val in zip(before_rotate_12, tmp):
        cube_flat[dst] = val

def rotate(cube_flat, face, before_rotate_12, after_rotate_12):
    rotate_face(cube_flat, face)
    rotate_12(cube_flat, before_rotate_12, after_rotate_12)

# 입력 받기
input = sys.stdin.readline
n = int(input())

# 풀이
for i in range(n):
    m = int(input())

    # 0 ~ 53번 면에 들어있는 색 표현
    cube_flat = [color[i] for i in range(6) for _ in range(9)]
    commands = input().split()

    for command in commands:
        face = mapping_table[command[0]]

        # -인 경우에는 3번, +인 경우에는 한 번 회전한다.
        cnt = rotate_dir[command[1]]

        # 12칸 회전
        before_rotate_12 = rotate_table[face]
        after_rotate_12 = before_rotate_12[3:] + before_rotate_12[:3]

        for i in range(cnt):
            rotate(cube_flat, face, before_rotate_12, after_rotate_12)


    for i in range(3):
        print(''.join(cube_flat[i*3:i*3+3]))
