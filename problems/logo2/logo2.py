import math, sys

t = int(input())


def apply_cmd(cmd, n, loc, dir):
    if cmd == "bk" or cmd == "rt":
        n *= -1
    if cmd == "fd" or cmd == "bk":
        loc[0] += math.cos(dir) * n
        loc[1] += math.sin(dir) * n
        return dir
    else:
        return dir + math.radians(n)


def cw(a, b):
    return a[0]*b[1] > a[1]*b[0]

for _ in range(t):
    c = int(input())
    loc = [0, 0]
    dir = 0
    for i in range(c):
        cmd, n = input().split()
        if n == "?":
            q_loc = loc.copy()
            q_type = cmd
            n = "0"
        n = int(n)
        dir = apply_cmd(cmd, n, loc, dir)

    adj = math.sqrt(loc[0] ** 2 + loc[1] ** 2)
    if q_type == "fd" or q_type == "bk":
        print(round(adj))
    else:
        hyp = math.sqrt(q_loc[0] ** 2 + q_loc[1] ** 2)
        theta = 2 * math.asin(adj / (hyp * 2))
        a = [-q_loc[0], -q_loc[1]]
        b = [loc[0] - q_loc[0], loc[1] - q_loc[1]]
        if (not cw(a, b) and q_type == "rt") or (cw(a, b) and q_type == "lt"):
            theta = 2 * math.pi - theta
        print(round(math.degrees(theta)) % 360)
