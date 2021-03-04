def solution(x, y):
    x, y = int(x), int(y)
    cnt = 0
    while x > 0 and y > 0:
        if x > y:
            cnt += x // y
            x %= y
        else:
            cnt += y // x
            y %= x
    return str(cnt - 1) if max(x, y) == 1 else "impossible"

