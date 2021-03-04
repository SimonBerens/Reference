from functools import lru_cache


def solution(h, q):
    @lru_cache(None)
    def s(h, v):
        root_no = n_elem_in_tree = 2 ** h - 1
        n_elem_in_subtree = n_elem_in_tree // 2
        l_child, r_child = n_elem_in_subtree, root_no - 1
        if v == l_child or v == r_child:
            return root_no
        elif v > n_elem_in_subtree:
            return s(h - 1, v - n_elem_in_subtree) + n_elem_in_subtree
        else:
            return s(h - 1, v)

    return [-1 if v == 2 ** h - 1 else s(h, v) for v in q]

