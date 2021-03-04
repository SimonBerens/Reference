import sys
sys.setrecursionlimit(1000000)

n, m = map(int, input().split())

g = [[] for _ in range(n)]

for _ in range(m):
    u, v, w = map(int, input().split())
    g[u].append((v, w))

s, t = map(int, input().split())

from heapq import *

pq = [(0, s, s)]
sssp_sdag = [[] for _ in range(n)]
min_w = [float("inf")] * n
seen = set()

while pq:
    path_w, v, p = heappop(pq)

    if v in seen:
        if path_w == min_w[v]:
            sssp_sdag[v].append(p)
        continue

    min_w[v] = path_w
    sssp_sdag[v].append(p)
    seen.add(v)

    for nbr, w in g[v]:
        if nbr not in seen:
            heappush(pq, (path_w + w, nbr, v))
        elif path_w + w == min_w[nbr]:
            sssp_sdag[nbr].append(v)

dfs_cnt = 0
dfs_num = [-1] * n
dfs_low = [-1] * n
articulation_vertex = [False] * n

g = [set() for _ in range(n)]

seen = set()
def gen(u):
    seen.add(u)
    for v in sssp_sdag[u]:
        g[u].add(v)
        g[v].add(u)
        if v not in seen:
            gen(v)

gen(t)

def mark_articulation_vertices(u, p):
    global dfs_cnt
    dfs_num[u] = dfs_cnt
    dfs_cnt += 1
    dfs_low[u] = dfs_num[u]

    for v in g[u]:
        if dfs_num[v] == -1:
            mark_articulation_vertices(v, u)

            if dfs_low[v] >= dfs_num[u]:
                articulation_vertex[u] = True

            dfs_low[u] = min(dfs_low[u], dfs_low[v])
        elif u != p:
            dfs_low[u] = min(dfs_low[u], dfs_num[v])


mark_articulation_vertices(s, None)
articulation_vertex[s] = True
articulation_vertex[t] = True

print(" ".join(str(i) for i in range(n) if articulation_vertex[i]))