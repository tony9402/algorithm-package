# https://www.acmicpc.net/problem/16934

import sys

input = sys.stdin.readline

class TrieNode:
    def __init__(self):
        self.child = {}
        self.num = 0

class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, nickname):
        node = self.root
        ret = []
        is_continue = True
        for char in nickname:
            if is_continue:
                ret.append(char)

            if char not in node.child:
                is_continue = False
                node.child[char] = TrieNode()
            node = node.child[char]

        node.num += 1
        ret = ''.join(ret) 
        if node.num > 1:
            ret += str(node.num)
        return ret

n = int(input())

trie = Trie()

for _ in range(n):
    nickname = input().strip()
    print(trie.insert(nickname))
