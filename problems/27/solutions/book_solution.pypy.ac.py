# https://www.acmicpc.net/problem/1991

preorder = []
inorder = []
postorder = []

class Node:
    def __init__(self, node, left, right):
        self.node = node
        self.left = left
        self.right = right

def travel(now: Node):
    if not now: return

    preorder.append(now.node)
    travel(now.left)
    inorder.append(now.node)
    travel(now.right)
    postorder.append(now.node)

n = int(input())
nodes = [Node(c, None, None) for c in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'] + [None]
tree = {c : node for (c, node) in zip('ABCDEFGHIJKLMNOPQRSTUVWXYZ.', nodes)}

for i in range(n):
    now, left, right = input().split()
    node = tree[now]
    left = tree[left]
    right = tree[right]

    node.left = left
    node.right = right

travel(tree['A'])

print(''.join(preorder))
print(''.join(inorder))
print(''.join(postorder))
