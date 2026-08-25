# https://www.acmicpc.net/problem/2263

import sys

sys.setrecursionlimit(10**7)
class Node: 
    # 오른쪽 트리를 먼저 만들기 때문에 right를 먼저 넣습니다.
    def __init__(self, value, right, left):
        self.value = value
        self.left = left
        self.right = right

n = int(input())
inorder = list(map(int, input().split()))
post_order = list(map(int, input().split()))
# inorder로 주어진 수가 어느 위치에 있는지 저장합니다.
position = {inorder[position] : position for position in range(n)}

index = n

def make_tree(left, right):
    global index
    if index == -1:
        return

    # 범위가 맞지 않으면 노드가 없는 것입니다.
    if left >= right:
        return None

    index -= 1

    # postorder의 가장 오른쪽에 있는 노드가 루트 노드입니다.
    root = post_order[index] 
    # inorder에서의 루트 노드 위치입니다.
    root_position = position[root]
    # inorder에서 루트를 기준으로 왼쪽 노드는 왼쪽 트리, 오른쪽 노드는 오른쪽 트리입니다.
    return Node(root, make_tree(root_position+1,right), make_tree(left, root_position))

# 전위 순회 한 결과를 출력합니다.
def pre_order(node: Node):
    if node is None:
        return

    print(node.value, end=' ')
    pre_order(node.left)
    pre_order(node.right)

pre_order(make_tree(0, n))
