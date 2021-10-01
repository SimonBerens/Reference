n = int(input())
a = list(map(int, input().split()))

from collections import Counter

c = Counter(a)

from functools import lru_cache

ps = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67]
P = len(ps)
ms = []

for i in range(71):
    m = 0
    for j, p in enumerate(ps):
        while i > 0 and i % p == 0:
            i //= p
            m ^= 1 << j
    ms.append(m)

M = 10 ** 9 + 7

import math
@lru_cache(None)
def dp(v, m):
    if v > 70:
        return int(m == 0)

    r =  math.ceil(2 ** (c[v] - 1)) * (dp(v + 1, m) + (dp(v + 1, m ^ ms[v]) if c[v] else 0)) % M
    return r

print(dp(1, 0) - 1)