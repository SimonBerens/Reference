#ifndef REFERENCE_UNION_FIND_H
#define REFERENCE_UNION_FIND_H

#include <vector>
#include <algorithm>
#include <unordered_map>

template<typename T>
class UnionFind {
private:
    std::unordered_map<T, std::size_t> to_elem;
    std::vector<std::size_t> elements;
    std::vector<std::size_t> sizes;
    size_t groups;

    std::size_t find_root(const T &val) {
        std::size_t start = to_elem[val], cur;
        for (cur = start; cur != elements[cur]; cur = elements[cur]);
        std::size_t ret = cur;
        for (cur = start; cur != ret; cur = elements[cur])
            elements[cur] = ret;
        return ret;
    }

public:
    template<typename Container>
    UnionFind(const Container &l) {
        std::vector<T> uniques(begin(l), end(l));
        uniques.erase(std::unique(begin(uniques), end(uniques)), end(uniques));
        to_elem.reserve(size(uniques));
        sizes.assign(size(uniques), 1);
        groups = size(uniques);
        for (int i = 0; i < size(uniques); ++i) {
            elements.push_back(i);
            to_elem.emplace(uniques[i], i);
        }
    }

    UnionFind(const std::initializer_list<T>& l) : UnionFind(l) {}

    bool disjoint(const T &a, const T &b)  {
        return find_root(a) != find_root(b);
    }

    std::size_t group_size(const T &a)  {
        return sizes[find_root(a)];
    }

    void unify(const T &a, const T &b) {
        auto root_a = find_root(a), root_b = find_root(b);
        if (root_a != root_b) {
            --groups;
            if (sizes[root_b] > sizes[root_a])
                std::swap(root_a, root_b);
            elements[root_b] = elements[root_a];
            sizes[root_a] += sizes[root_b];
        }
    }
};

#endif //REFERENCE_UNION_FIND_H
