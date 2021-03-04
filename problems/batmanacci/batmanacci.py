import sys
sys.setrecursionlimit(1000000)

n, k = map(int, input().split())

from functools import lru_cache

@lru_cache(None)
def fib(n):
    if n <= 2:
        return 1
    return fib(n - 1) + fib(n - 2)


while n > 2:
    if n > 100 or k <= fib(n - 2):
        n -= 2
    else:
        k -= fib(n - 2)
        n -= 1

print("N" if n == 1 else "A")
