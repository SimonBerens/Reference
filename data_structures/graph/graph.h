#ifndef REFERENCE_GRAPH_H
#define REFERENCE_GRAPH_H

#include <vector>
#include <memory>
#include <initializer_list>

// todo c++20 concepts
template<
        typename EdgeCostType,
        template<typename> typename VertexWrapper,
        template<typename, typename> typename Container
>
struct Graph;


template<typename GraphType>
struct Edge;
template<typename GraphType>
struct Vertex;

template<
        typename EdgeCostType,
        template<typename> typename VertexWrapper = std::shared_ptr,
        template<typename, typename> typename  Container = std::vector
>
struct Graph {
    typedef EdgeCostType edge_cost_t;
    typedef VertexWrapper<Vertex<Graph>> wrapped_vertex_t;
    typedef Container<Edge<Graph>, std::allocator<Edge<Graph>>> container_t;
    // todo need two template parameters
    // todo something to do with partial specialization, clang -frelaxed-template-template-args, idk
};



namespace std {
    template<typename GraphType>
    struct hash<Edge<GraphType>> {
        std::size_t operator()(const Edge<GraphType> &edge) const {
            return hash<decltype(edge.cost)>()(edge.cost) ^
                   hash<decltype(edge.predecessor)>()(edge.predecessor) ^
                   hash<decltype(edge.successor)>()(edge.successor);
        }
    };
}

template<typename GraphType>
struct Vertex {
    typedef typename GraphType::container_t container_t;
    container_t direct_successors;

    Vertex() {}

    Vertex(const container_t &directSuccessors) : direct_successors(directSuccessors) {}

    Vertex(const std::initializer_list<typename container_t::value_type> &list) : direct_successors(list) {}
};

template<typename GraphType>
struct Edge {
    typedef typename GraphType::edge_cost_t edge_cost_t;
    typedef typename GraphType::wrapped_vertex_t wrapped_vertex_t;
    edge_cost_t cost;
    wrapped_vertex_t predecessor;
    wrapped_vertex_t successor;

    Edge(const edge_cost_t &cost,
         const wrapped_vertex_t &predecessor,
         const wrapped_vertex_t &successor) :
            cost(cost), predecessor(predecessor), successor(successor) {}

    bool operator<(const Edge &rhs) const {
        return cost < rhs.cost;
    }

    bool operator>(const Edge &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Edge &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Edge &rhs) const {
        return !(*this < rhs);
    }
};

Graph<int> g;
#endif //REFERENCE_GRAPH_H
