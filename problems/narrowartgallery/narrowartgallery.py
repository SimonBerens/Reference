from functools import lru_cache

n, k = map(int, input().split())

g = []
for i in range(n):
    g.append(list(map(int, input().split())))


@lru_cache(None)
def dp(r, t, k):
    if r == n:
        return float("-inf") if k > 0 else 0
    if k == 0:
        return sum(g[r]) + dp(r + 1, t, k)
    if t == 0:
        return max(sum(g[r]) + dp(r + 1, 0, k), g[r][1] + dp(r + 1, 1, k - 1), g[r][0] + dp(r + 1, 2, k - 1))
    elif t == 1:
        return max(sum(g[r]) + dp(r + 1, 0, k), g[r][1] + dp(r + 1, 1, k - 1))
    else:
        return max(sum(g[r]) + dp(r + 1, 0, k), g[r][0] + dp(r + 1, 2, k - 1))


print(dp(0, 0, k))
