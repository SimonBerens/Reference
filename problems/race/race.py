import sys

sys.stdin = open("race.in", "r")
sys.stdout = open("race.out", "w")

k, n = map(int, input().split())


def bs(lo, hi, f):
    while lo < hi:
        m = (lo + hi) // 2
        if f(m):
            hi = m
        else:
            lo = m + 1
    return lo


for _ in range(n):
    x = int(input())

    if x * (x + 1) // 2
