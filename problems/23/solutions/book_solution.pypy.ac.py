# https://www.acmicpc.net/problem/2003

n, m = map(int, input().split())
nums = list(map(int, input().split()))

s = 0
e = 0
number_sum = 0
result = 0

# e가 끝까지 왔을 경우 
while e < len(nums) or s < e:
    if e == len(nums):
        number_sum -= nums[s]
        s += 1
    else:
        if number_sum < m:
            number_sum += nums[e]
            e += 1
        else:
            number_sum -= nums[s]
            s += 1

    if number_sum == m:
        result += 1

print(result)
