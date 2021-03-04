import itertools
from collections import *

for i in itertools.count():
    n, m = map(int, input().split())
    if n == m == 0:
        break
    g = defaultdict(set)
    gt = defaultdict(set)
    s = []
    for _ in range(m):
        a, b = input().split()
        g[a].add(b)
        g[b]
        gt[b].add(a)
        gt[a]
    seen = set()


    def kosaraju(cur, graph):
        seen.add(cur)
        for nbr in graph[cur]:
            if nbr not in seen:
                kosaraju(nbr, graph)
        s.append(cur)


    for name in g.keys():
        if name not in seen:
            kosaraju(name, g)
    seen.clear()
    sccs = []
    rs = list(reversed(s))
    s.clear()
    for name in rs:
        if name not in seen:
            kosaraju(name, gt)
            sccs.append(s.copy())
            s.clear()
    print(f"Calling circles for data set {i + 1}:")
    for scc in sccs:
        print(", ".join(scc))
    print()