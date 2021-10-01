from heapq import *
from fractions import Fraction

import math

while True:
    n, b = map(int, input().split())
    if n == -1:
        exit(0)
    cities = []
    for _ in range(n):
        heappush(cities, (-Fraction(int(input())), 1))
    for _ in range(b - n):
        f, boxes = heappop(cities)
        heappush(cities, (Fraction(f * boxes, boxes + 1), boxes + 1))
    print(math.ceil(-heappop(cities)[0]))
    input()
