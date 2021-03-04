from collections import defaultdict
from heapq import *

n, t = map(int, input().split())

d = defaultdict(list)
for ci, ti in iter(tuple(map(int, input().split())) for i in range(n)):
    d[min(ti, t - 1)].append(ci)

cost = 0
h = []
for ti in reversed(range(t)):
    for ci in d[ti]:
        heappush(h, -ci)
    if h:
        cost += -heappop(h)

print(cost)
