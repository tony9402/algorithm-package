MOD = 10007

n = int(input())

tiles = [0] * (n + 2)
tiles[0] = 1
tiles[1] = 1

for i in range(2, n + 1):
    tiles[i] = (tiles[i - 1] + tiles[i - 2]) % MOD

print(tiles[n])
