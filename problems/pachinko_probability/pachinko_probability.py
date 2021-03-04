from functools import lru_cache

n = int(input())
m = int(input())

rgraph = [[] for _ in range(n)]
ends = set(i for i in range(n))
for _ in range(m):
    x, y = (int(i) for i in input().split())
    rgraph[y].append(x)
    ends.discard(x)

k = int(input())
gates = set(int(input()) for _ in range(k))


@lru_cache(None)
def count_paths(node):
    if not rgraph[node]:
        return 1
    return sum(count_paths(successor) for successor in rgraph[node])


print(f"winning paths {sum(count_paths(gate) for gate in gates)}")
print(f"total paths {sum(count_paths(end) for end in ends)}")
