import math

def bs(lo, hi, f):
    while lo < hi:
        m = (lo + hi) // 2
        if f(m):
            hi = m
        else:
            lo = m + 1
    return lo


while True:
    x = int(input())
    if x == 0:
        break
    mp = 0

    neg = x < 0
    x = abs(x)

    for p in range(1, int(math.log2(x)) + 5, 2 if neg else 1):
        max_base = bs(2, x, lambda b: b ** p >= x)
        if max_base ** p == x:
            mp = p

    print(mp)
