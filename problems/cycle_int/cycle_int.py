def baseN(num, b, numerals="0123456789abcdefghijklmnopqrstuvwxyz"):
    return ((num == 0) and numerals[0]) or (baseN(num // b, b, numerals).lstrip(numerals[0]) + numerals[num % b])


def solution(n: str, b: int, seen=None, iter_cnt=0):
    if not seen:
        seen = {}
    if n in seen:
        return iter_cnt - seen[n]
    seen[n] = iter_cnt
    k = len(n)
    digits = list(n)
    x = int("".join(sorted(digits, reverse=True)), b)
    y = int("".join(sorted(digits)), b)
    z = x - y
    strz = baseN(z, b)
    return solution("0" * (k - len(strz)) + strz, b, seen=seen, iter_cnt=iter_cnt + 1)
