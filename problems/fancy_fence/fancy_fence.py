t = int(input())

for i in range(t):
    print("YES" if 360 % (180 - int(input())) == 0 else "NO")