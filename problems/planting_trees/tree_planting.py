print(max(i + n + 1 for i, n in enumerate(sorted(map(int, (input(), input())[1].split()))[::-1], 1)))