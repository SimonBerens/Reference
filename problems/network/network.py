while True:
    n = int(input())
    if n == 0:
        break

    g = [[] for i in range(n)]

    while True:
        place, *connections = map(int, input().split())
        if place == 0:
            break
        for connection in connections:
            g[place - 1].append(connection - 1)
            g[connection - 1].append(place - 1)

    dfs_num = [-1] * n
    dfs_low = [-1] * n
    dfs_parent = [-1] * n
    articulation_vertex = [False] * n

    dfsCnt = rootChildren = 0

    def dfs(u, r):
        global dfsCnt, rootChildren
        dfs_num[u] = dfsCnt
        dfsCnt += 1
        dfs_low[u] = dfs_num[u]
        for v in g[u]:
            if dfs_num[v] == -1:
                dfs_parent[v] = u
                if u == r:
                    rootChildren += 1
                dfs(v, r)

                if dfs_low[v] >= dfs_num[u]:
                    articulation_vertex[u] = True

                dfs_low[u] = min(dfs_low[u], dfs_low[v])
            elif v != dfs_parent[u]:
                dfs_low[u] = min(dfs_low[u], dfs_num[v])

    dfs(0, 0)
    articulation_vertex[0] = rootChildren > 1
    print(sum(articulation_vertex))