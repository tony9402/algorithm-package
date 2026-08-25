import sys

input = sys.stdin.readline

n, k = map(int, input().split())
beads = list(map(int, input().split()))


def possible(limit, build):
    groups = []
    group_count = 1
    current_sum = 0
    current_size = 0

    for index, bead in enumerate(beads):
        remaining_items = n - index
        remaining_groups = k - group_count
        must_split = remaining_items == remaining_groups

        if current_sum + bead > limit or must_split:
            if group_count == k:
                return False, []
            if build:
                groups.append(current_size)
            group_count += 1
            current_sum = bead
            current_size = 1
        else:
            current_sum += bead
            current_size += 1

    if build:
        groups.append(current_size)
    return group_count <= k, groups


left = max(beads)
right = sum(beads)

while left < right:
    mid = (left + right) // 2
    ok, _ = possible(mid, False)
    if ok:
        right = mid
    else:
        left = mid + 1

_, answer_groups = possible(left, True)

print(left)
print(*answer_groups)
