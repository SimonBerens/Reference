#ifndef REFERENCE_DIJKSTRA_H
#define REFERENCE_DIJKSTRA_H

#include <vector>
#include <memory>
#include <queue>
#include <unordered_set>
#include <functional>
#include <optional>

#include "../../data_structures/graph/graph.h"

template<typename GraphType>
struct Path {
    typedef typename GraphType::edge_cost_t edge_cost_t;
    edge_cost_t path_cost;
    typedef typename GraphType::wrapped_vertex_t wrapped_vertex_t;
    wrapped_vertex_t cur_vertex;

    Path(edge_cost_t pathCost, const wrapped_vertex_t &curVertex) :
            path_cost(pathCost), cur_vertex(curVertex) {}

    bool operator<(const Path &rhs) const {
        return path_cost < rhs.path_cost;
    }

    bool operator>(const Path &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Path &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Path &rhs) const {
        return !(*this < rhs);
    }
};


template<typename GraphType, typename Compare = std::greater<Path<GraphType>>>
std::optional<typename GraphType::edge_cost_t> dijkstra(
        const typename GraphType::wrapped_vertex_t& source,
        const typename GraphType::wrapped_vertex_t& dest,
        const typename GraphType::edge_cost_t init = GraphType::edge_cost_t(),
        std::function<const typename GraphType::edge_cost_t(const typename GraphType::edge_cost_t &, const typename GraphType::edge_cost_t &)>
        cost_function = std::plus<typename GraphType::edge_cost_t>{}) {

    using edge_cost_t = typename GraphType::edge_cost_t;
    using wrapped_vertex_t = typename GraphType::wrapped_vertex_t;
    std::priority_queue<Path<GraphType>, std::vector<Path<GraphType>>, Compare> pq;
    pq.emplace(init, source);
    std::unordered_set<wrapped_vertex_t> seen;
    seen.insert(source);
    while (size(pq)) {
        const auto[cur_cost, vertex] = pq.top();
        pq.pop();
        if (vertex == dest)
            return {cur_cost};
        seen.insert(vertex);
        for (const auto &edge: vertex->direct_successors)
            if (seen.count(edge.successor) == 0) // todo c++20 contains
                pq.emplace(cost_function(cur_cost, edge.cost), edge.successor);
    }
    return {};
}


#endif //REFERENCE_DIJKSTRA_H
