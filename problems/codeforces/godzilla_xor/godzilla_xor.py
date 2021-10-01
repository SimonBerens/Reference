n = int(input())

BITS = 29
basis = [0] * BITS
pretty = [0]

for _ in range(n):
    t, k = map(int, input().split())
    if t == 1:
        for i in range(BITS):
            if (k & (1 << i)) == 0:
                continue

            if basis[i] == 0:
                bs = [v for v in basis if v != 0]
                for p in pretty[:]:
                    pretty.append(p ^ k)
                pretty.sort()
                basis[i] = k
                break

            k ^= basis[i]
    else:
        try:
            print(pretty[k - 1])
        except IndexError:
            print("poop")
