# https://www.acmicpc.net/problem/11441

n = int(input())
nums = [0] + [int(i) for i in input().split()]
for i in range(1, n+1):
    nums[i] += nums[i-1]

m = int(input())
for _ in range(m):
    s, e = map(int, input().split())
    print(nums[e] - nums[s-1])