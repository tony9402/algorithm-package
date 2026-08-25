# https://www.acmicpc.net/problem/7453

n = int(input())
A, B, C, D = [],[],[],[]

for i in range(n):
    a, b, c, d = map(int,input().split())
    A.append(a)
    B.append(b)
    C.append(c)
    D.append(d)

AB = sorted([a+b for a in A for b in B])
CD = sorted([c+d for c in C for d in D])

i = 0
j = len(CD)-1

result = 0
while i < len(AB) and j >= 0:
    if AB[i] + CD[j] == 0:
        # 배열에서 같은 값이 있으면 해당 지점과 다른 값이 나올때 까지 지점을 이동합니다.
        store_i = i
        store_j = j

        while i < len(AB) and AB[store_i] == AB[i]:
            i += 1
        while j >= 0 and CD[store_j] == CD[j]:
            j -= 1

        result += (i - store_i)*(store_j - j)
    elif AB[i] + CD[j] < 0:
        i += 1
    else:
        j -= 1

print(result)
