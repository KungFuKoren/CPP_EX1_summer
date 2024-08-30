#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP
//  kkorenn1@gmail.com 209271535

#include "Graph.hpp"
#include <string>
#include <vector>

namespace ariel {

class Algorithms {
public:
    static bool isConnected(const Graph& graph);
    static std::string shortestPath(const Graph& graph, int start, int end);
    static bool isContainsCycle(const Graph& graph);
    static std::string isBipartite(const Graph& graph);
    static bool negativeCycle(const Graph& graph);

private:
    static bool dfsCheckCycle(const Graph& graph, size_t v, std::vector<bool>& visited, int parent);
    static bool isBipartiteUtil(const Graph& graph, size_t v, std::vector<int>& colors);
};

} // namespace ariel

#endif // ALGORITHMS_HPP