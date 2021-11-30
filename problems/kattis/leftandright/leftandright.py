n = int(input())
s = "L" + input() + "R"

from itertools import groupby

res = []

i = 0

for k, g in groupby(s):
    n = len(list(g))
    res.append([])
    for _ in range(n + (1 if k == "L" else -1)):
        res[-1].append(i)
        i += 1
    if k == "L":
        res[-1].reverse()

rres = []
for l in res:
    for e in l:
        rres.append(e)

del rres[rres.index(0)]

print("\n".join(map(str, rres)))