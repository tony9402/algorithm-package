# https://www.acmicpc.net/problem/2748

# 메모이제이션
cache = [-1]*91

def fibonacci_memoization(n):
    if cache[n] != -1: return cache[n]
    if n == 0: return 0
    if n == 1: return 1
    cache[n] = fibonacci_memoization(n-1) + fibonacci_memoization(n-2)
    return cache[n] 

print(fibonacci_memoization((int(input()))))