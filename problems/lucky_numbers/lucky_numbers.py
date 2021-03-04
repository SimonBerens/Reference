n = int(input())

res = [0] * (n + 1)


def dfs(cn, nd):
    if nd > n:
        return

    res[nd] += 1

    for i in range(10):
        ncn = 10 * cn + i
        if ncn % (nd + 1) == 0:
            dfs(ncn, nd + 1)


for i in range(1, 10):
    dfs(i, 1)

print(res[-1])
