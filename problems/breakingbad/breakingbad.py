from itertools import groupby
from collections import defaultdict
import sys

sys.setrecursionlimit(1000000)
n = int(input())


g = defaultdict(set)

for _ in range(n):
    g[input()]

m = int(input())

for _ in range(m):
    a, b = input().split()
    g[a].add(b)
    g[b].add(a)

coloring = {}


def dfs(item, p):
    coloring[item] = not p
    return all(dfs(x, not p) if x not in coloring else coloring[x] == p for x in g[item])


for item in g.keys():
    if item not in coloring:
        if not dfs(item, True):
            print("impossible")
            exit(0)

for k, g in groupby(g.keys(), key=coloring.__getitem__):
    print(" ".join(g))
