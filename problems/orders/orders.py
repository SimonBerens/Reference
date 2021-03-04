from functools import lru_cache
import sys

sys.setrecursionlimit(1000000)

n = int(input())
prices = list(map(int, input().split()))
m = int(input())


@lru_cache(None)
def answer(c):
    if c < 0:
        return 0, None
    if c == 0:
        return 1, tuple([0] * n)

    sols = set()

    for i, p in enumerate(prices):

        cnt, a = answer(c - p)

        if cnt == 1:
            t = list(a)
            t[i] += 1
            sols.add(tuple(t))

            if len(sols) > 1:
                return 2, None
        elif cnt == 2:
            return 2, None

    if not sols:
        return 0, None
    else:
        return 1, sols.pop()


for order in map(int, input().split()):
    cnt, a = answer(order)
    if cnt == 0:
        print("Impossible")
    elif cnt == 1:
        print(" ".join(str(i + 1) for i, cnt in enumerate(a) for _ in range(cnt)))
    else:
        print("Ambiguous")
