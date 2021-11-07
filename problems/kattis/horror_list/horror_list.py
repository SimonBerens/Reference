n, h, l = map(int, input().split())

srcs = list(map(int, input().split()))

g = [[] for _ in range(n)]

for _ in range(l):
    a, b, = map(int, input().split())
    g[a].append(b)
    g[b].append(a)

his = [float("inf") for _ in range(n)]

from collections import deque

q = deque()
for src in srcs:
    q.append((src, 0))

vis = [0 for _ in range(n)]

while q:
    u, hi = q.popleft()
    if vis[u]:
        continue
    vis[u] = 1
    his[u] = hi
    for v in g[u]:
        if not vis[v]:
            q.append((v, hi + 1))

print(his.index(max(his)))


