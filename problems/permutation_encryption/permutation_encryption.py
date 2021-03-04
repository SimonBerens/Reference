while True:
    n, *p = map(int, input().split())
    if n == 0:
        exit()
    s = input()
    res = ""
    for i in range(0, len(s), n):
        for j in range(n):
            idx = i + p[j] - 1
            res += " " if idx >= len(s) else s[idx]
    print(f"'{res}'")
