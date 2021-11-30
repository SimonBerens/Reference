c, s = input().split()

from itertools import groupby

if c == "E":
    res = []
    for k, g in groupby(s):
        n = len(list(g))
        res.append(k)
        res.append(n)
    print("".join(map(str, res)))
else:
    res = []
    for c, cnt in zip(s[::2], s[1::2]):
        for _ in range(int(cnt)):
            res.append(c)
    print("".join(res))