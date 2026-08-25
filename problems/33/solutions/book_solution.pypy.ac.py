# https://www.acmicpc.net/problem/1992

n = int(input())
quad = [[c for c in input()] for _ in range(n)]

def quad_tree(i, j, n):
    quad_sum = 0

    # 입력이 string이므로 int로 변환해서 더해줍니다.
    for row in quad[i:i+n]:
        quad_sum += sum(map(int, row[j:j+n]))

    # 모두 1이면 '1'을 반환합니다.
    if quad_sum == n*n:
        return '1'

    # 모두 0이면 '0'을 반환합니다.
    elif quad_sum == 0:
        return '0'

    # 0과 1이 섞여있으면 4 부분으로 나눠 함수를 호출합니다.
    return '(' + quad_tree(i, j, n//2) + \
            quad_tree(i, j+n//2, n//2) + \
            quad_tree(i+n//2, j, n//2) + \
            quad_tree(i+n//2, j+n//2, n//2) + ')'

print(quad_tree(0, 0, n))
