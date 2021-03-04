while True:
    try:
        pattern = input()
        text = input()

        fail_to = [0] * len(pattern)
        i = 1
        m = 0
        while i < len(pattern):
            if pattern[i] == pattern[m]:
                m += 1
                fail_to[i] = m
                i += 1
            elif m != 0:
                m = fail_to[m - 1]
            else:
                fail_to[i] = 0
                i += 1

        idxs = []

        i = 0
        j = 0

        while j < len(text):
            if pattern[i] != text[j]:
                if i == 0:
                    j += 1
                else:
                    i = fail_to[i - 1]
            else:
                i += 1
                j += 1
                if i == len(pattern):
                    idxs.append(j - i)
                    i = fail_to[i - 1]

        print(" ".join(map(str, idxs)))
    except EOFError:
        break
