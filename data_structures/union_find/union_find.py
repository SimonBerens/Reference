class UnionFind:
    def __init__(self, collection=None):
        self.num_groups = 0
        self._elem_to_root = {}
        self._root_to_size = {}
        if collection:
            for elem in collection:
                self.add(elem)

    def add(self, elem):
        if elem not in self._elem_to_root:
            self.num_groups += 1
            self._elem_to_root[elem] = elem
            self._root_to_size[elem] = 1

    def find_root(self, elem):
        cur = elem
        visited = []
        while self._elem_to_root[cur] != cur:
            visited.append(cur)
            cur = self._elem_to_root[cur]
        for v in visited:
            self._elem_to_root[v] = cur
        return cur

    def disjoint(self, elem1, elem2):
        return self.find_root(elem1) != self.find_root(elem2)

    def union(self, elem1, elem2):
        r1, r2 = self.find_root(elem1), self.find_root(elem2)
        if r1 != r2:
            s1, s2 = self._root_to_size[r1], self._root_to_size[r2]
            if s1 > s2:
                r1, r2 = r2, r1
                s1, s2 = s2, s1
            self._elem_to_root[r1] = r2
            self._root_to_size[r2] += s1
            self.num_groups -= 1

    def get_group_size(self, elem):
        return self._root_to_size[self.find_root(elem)]
