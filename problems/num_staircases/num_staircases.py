from functools import lru_cache


def solution(n: int) -> int:
    @lru_cache(None)
    def dp(n_bricks, height):
        if n_bricks > height * (height + 1) // 2 or n_bricks < height:
            return 0
        if height == n_bricks:
            return 1
        return sum(dp(n_bricks - height, h) for h in range(1, height))

    return sum(dp(n, h) for h in range(2, n))
