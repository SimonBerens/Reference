n = int(input())
a = list(map(int, input().split()))


from functools import lru_cache

from math import comb

M = 10 ** 9 + 7

@lru_cache(None)
def dp(l, i):
    if i > 9:
        return int(l == 0)
    if l < 0:
        return 0

    if i == l == 0:
        return 0

    m = l - 1 if i == 0 else l
    extra = dp(l - 1, i) if i == 0 else 0

    return (sum((comb(m, k) % M) * dp(l - k, i + 1) for k in range(a[i], l + 1)) + extra) % M

print(dp(n, 0))


