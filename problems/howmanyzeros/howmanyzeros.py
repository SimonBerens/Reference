def num_zeros_up_to_k(k):
    if k < 0:
        return 0

    s = str(k)[::-1]
    from functools import lru_cache
    @lru_cache(None)
    def dp(pos, limited, all_z):
        if pos == 0:
            return 1

        limit = 9
        if limited:
            limit = int(s[pos])

        res = 0
        res += dp(pos - 1, limited and limit == 0, all_z)

        if limited and limit == 0:
            res += int(s[:pos][::-1]) + 1
        elif not all_z:
            res += 10 ** pos

        for d in range(1, limit + 1):
            res += dp(pos - 1, limited and d == limit, False)

        return res

    return dp(len(s) - 1, True, True)



while True:
    m, n = map(int, input().split())
    if m < 0:
        break
    print(num_zeros_up_to_k(n) - num_zeros_up_to_k(m - 1))

