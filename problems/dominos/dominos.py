import sys
sys.setrecursionlimit(1000000)

t = int(input())

for i in range(t):
    n, m = map(int, input().split())
    g, gt = [set() for _ in range(n + 1)], [set() for _ in range(n + 1)]
    for _ in range(m):
        x, y = map(int, input().split())
        g[x].add(y)
        gt[y].add(x)

    seen = set()
    curseen = set()
    topo = []

    def dfs(cur, graph):
        res = True
        seen.add(cur)
        curseen.add(cur)
        for nbr in graph[cur]:
            if nbr not in seen:
                res &= dfs(nbr, graph)
            elif nbr not in curseen:
                res = False
        topo.append(cur)
        return res

    for dom in range(1, n + 1):
        if dom not in seen:
            dfs(dom, g)

    rt = list(reversed(topo))
    topo.clear()
    seen.clear()
    curseen.clear()

    res = 0
    for dom in rt:
        if dom not in seen:
            res += dfs(dom, gt)
            curseen.clear()

    print(res)
