n, m = map(int, input().split())
places = []
w = [[float("inf")] * n for _ in range(n)]
nxt = [[None] * n for _ in range(n)]

for i in range(n):
    x = list(map(int, input().split()))
    x[0] *= 5
    places.append(x)  # floor, x, y
    w[i][i] = 0
    nxt[i][i] = i


def dist(a, b):
    import math
    return math.sqrt(sum((x - y) ** 2 for x, y in zip(a, b)))


def calc_w(p1idx, p2idx, con_type):
    if con_type == "walking" or con_type == "stairs":
        return dist(places[p1idx], places[p2idx])
    elif con_type == "lift" or con_type == "escalator":
        return 1
    else:  # escalatorr
        return dist(places[p1idx], places[p2idx]) * 3


for i in range(m):
    *p, con_type = input().split()
    p1idx, p2idx = map(int, p)
    w[p1idx][p2idx] = calc_w(p1idx, p2idx, con_type)
    w[p2idx][p1idx] = calc_w(p1idx, p2idx, con_type + ("r" if con_type == "escalator" else ""))
    nxt[p1idx][p2idx] = p2idx
    nxt[p2idx][p1idx] = p1idx

for k in range(len(places)):
    for i in range(len(places)):
        for j in range(len(places)):
            if w[i][j] > w[i][k] + w[k][j]:
                w[i][j] = w[i][k] + w[k][j]
                nxt[i][j] = nxt[i][k]

q = int(input())
for _ in range(q):
    u, v = map(int, input().split())
    path = [u]
    while u != v:
        u = nxt[u][v]
        path.append(u)
    print(" ".join(map(str, path)))
