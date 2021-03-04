from math import sqrt

while True:
    try:
        n, l, w = map(int, input().split())
        intervals = []
        for i in range(n):
            x, r = map(int, input().split())
            if r > w / 2:
                interval_width = sqrt(r ** 2 - (w ** 2 / 4))
                intervals.append((x - interval_width, x + interval_width))
        intervals.sort()

        end = 0
        i = 0
        res = 0
        while True:
            new_end = end
            while i < len(intervals) and intervals[i][0] <= end:
                new_end = max(new_end, intervals[i][1])
                i += 1
            res += 1
            if new_end >= l:
                print(res)
                break
            if new_end == end:
                print(-1)
                break
            end = new_end
    except EOFError:
        exit()
