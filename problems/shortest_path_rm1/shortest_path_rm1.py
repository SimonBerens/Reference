from collections import deque


def solution(map):
    ds = [(1, 0), (0, 1), (-1, 0), (0, -1)]
    seen = {(0, 0, False)}
    q = deque([(1, (0, 0), False)])
    h, w = len(map), len(map[0])
    while q:
        path_len, (x, y), flipped = q.popleft()
        if x == w - 1 and y == h - 1:
            return path_len
        for dx, dy in ds:
            nx, ny = x + dx, y + dy
            if 0 <= nx < w and 0 <= ny < h and (nx, ny, flipped) not in seen:
                if map[ny][nx] == 1 and not flipped:
                    seen.add((nx, ny, not flipped))
                    q.append((path_len + 1, (nx, ny), not flipped))
                elif map[ny][nx] != 1:
                    seen.add((nx, ny, flipped))
                    q.append((path_len + 1, (nx, ny), flipped))
    return float("inf")


print(solution([[0, 0, 0, 0, 0, 0],
                [1, 1, 1, 1, 1, 0],
                [0, 0, 0, 0, 0, 0],
                [0, 1, 1, 1, 1, 1],
                [0, 1, 1, 1, 1, 1],
                [0, 0, 0, 0, 0, 0]]))

print(solution([[0, 0],
                [1, 0],
                [0, 0],
                [0, 1],
                [0, 1],
                [1, 0]]))

print(solution([[0, 1, 0, 1],
                [0, 1, 0, 1],
                [0, 0, 1, 0]]))