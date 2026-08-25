# https://www.acmicpc.net/problem/1920

def binary_search(dest, arr):
    start = 0
    end = len(arr)

    while start < end:
        mid = (start+end ) // 2
        num = arr[mid]

        if dest == num:
             return 1
        elif num < dest:
            start = mid + 1
        else:
            end = mid

    return 0


N = int(input())
A = list(map(int, input().split()))
M = int(input())

A.sort()
for num in map(int, input().split()):
    print(binary_search(num, A))
