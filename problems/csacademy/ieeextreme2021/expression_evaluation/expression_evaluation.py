# bruh

t = int(input())

M = 10 ** 9 + 7

from itertools import product
import sys

sys.setrecursionlimit(10 ** 6)

for _ in range(t):
    i = input()
    if any(("".join(s) in i) for s in product("+-*", repeat=2)) or (set(i) & set("0123456789()+*-") != set(i)) :
        print("invalid")
        continue
    try:
        eval(i.replace('+', '^').replace('-', '^'))
        print((eval(i) + M) % M)
    except:
        print("invalid")