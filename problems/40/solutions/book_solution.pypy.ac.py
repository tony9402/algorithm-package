# https://www.acmicpc.net/problem/14426

class TrieNode:
    def __init__(self):
        self.child = {}

class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word):
        node = self.root

        for char in word:
            if char not in node.child:
                node.child[char] = TrieNode()
            node = node.child[char]

    def find_prefix(self, prefix):
        node = self.root

        for char in prefix:
            if char not in node.child:
                return False
            node = node.child[char]

        return True

n, m = map(int, input().split())

trie = Trie()

answer = 0

for _ in range(n):
    trie.insert(input())

for _ in range(m):
    prefix = input()
    if trie.find_prefix(prefix):
        answer += 1

print(answer)
