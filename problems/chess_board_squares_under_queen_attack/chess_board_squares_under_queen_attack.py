def naive(width, height):
    def go(r, c, dr, dc):
        if 0 <= r < height and 0 <= c < width:
            return 1 + go(r + dr, c + dc, dr, dc)
        return 0

    res = 0
    for row in range(height):
        for col in range(width):
            for dr in (-1, 0, 1):
                for dc in (-1, 0, 1):
                    res += go(row, col, row + dr, col + dc)
    return res


def optimized(width, height):
    res = 0
    for row in range(width):
        for col in range(height):
            res += width - 1 + height - 1
            res += min(col - row + height - 1, height - 1) - max(0, col - row)
            res += min(row + col + 1, width) - max(row + col - height + 2, 1)
    return res


def constant(width, height):
    if height > width:
        height, width = width, height
    return 2 * ((width - height + 1) * height * (height - 1) + 2 * (height - 2) * (height - 1) * height // 3) + \
           (width * height * (width - 1 + height - 1))
