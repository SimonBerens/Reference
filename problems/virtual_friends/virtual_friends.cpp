#include <bits/stdc++.h>
using namespace std;


#ifndef REFERENCE_UNION_FIND_H
#define REFERENCE_UNION_FIND_H

#include <vector>
#include <algorithm>
#include <unordered_map>

template<typename T>
class UnionFind {
public:

    UnionFind() : groups(0) {};

    bool add(const T &a) {
        if (to_elem.count(a) > 0) {
            return false;
        } else {
            to_elem[a] = elements.size();
            elements.push_back(elements.size());
            sizes.push_back(1);
            groups += 1;
            return true;
        }
    }

    template<typename Container>
    explicit UnionFind(const Container &l) : groups(0) {
        for (const auto &item : l)
            add(item);
    }

    UnionFind(const std::initializer_list<T>& l) : UnionFind<std::initializer_list<T>>(l) {}

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
private:
    std::unordered_map<T, std::size_t> to_elem;
    std::vector<std::size_t> elements;
    std::vector<std::size_t> sizes;
    size_t groups{};

    std::size_t find_root(const T &val) {
        std::size_t start = to_elem[val], cur;
        for (cur = start; cur != elements[cur]; cur = elements[cur]);
        std::size_t ret = cur;
        for (cur = start; cur != ret; cur = elements[cur])
            elements[cur] = ret;
        return ret;
    }
};

#endif //REFERENCE_UNION_FIND_H


int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        UnionFind<string> friends;
        int f;
        cin >> f >> ws;
        for (int j = 0; j < f; ++j) {
            string line, a, b;
            getline(cin, line);
            int pos = line.find(' ');
            a = line.substr(0, pos);
            b = line.substr(pos + 1, line.size());
            friends.add(a);
            friends.add(b);
            friends.unify(a, b);
            cout << friends.group_size(a) << "\n";
        }
    }
}