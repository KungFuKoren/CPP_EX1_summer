#include "Algorithms.hpp"
#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <limits>
#include <vector>
//  kkorenn1@gmail.com 209271535

namespace ariel {
//Running BFS and checking if all vertices are visited.
bool Algorithms::isConnected(const Graph& graph) {
    size_t numVertices = graph.getNumVertices();
    if (numVertices == 0) return true;

    std::vector<bool> visited(numVertices, false);
    std::queue<int> q;
    q.push(0);
    visited[0] = true;
    int visitedCount = 1;

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (size_t i = 0; i < numVertices; ++i) {
            if (graph.getAdjMatrix()[static_cast<size_t>(v)][i] != 0 && !visited[i]) {
                q.push(static_cast<int>(i));
                visited[i] = true;
                visitedCount++;
            }
        }
    }

    return visitedCount == numVertices;
}
//Running Bellman-Ford to check for a path in a fraph with negative weighted edges. and checks no negative cycles
std::string Algorithms::shortestPath(const Graph& graph, int start, int end) {
    size_t numVertices = graph.getNumVertices();
    if (start >= numVertices || end >= numVertices || start < 0 || end < 0) {
        return "-1";
    }
    std::vector<int> distances(numVertices, std::numeric_limits<int>::max());
    std::vector<int> predecessors(numVertices, -1);
    distances[static_cast<size_t>(start)] = 0;
    // Relax edges repeatedly
    for (size_t k = 0; k < numVertices - 1; ++k) {
        for (size_t u = 0; u < numVertices; ++u) {
            for (size_t v = 0; v < numVertices; ++v) {
                if (graph.getAdjMatrix()[u][v] != 0) {
                    int weight = graph.getAdjMatrix()[u][v];
                    if (distances[u] != std::numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                        distances[v] = distances[u] + weight;
                        predecessors[v] = u;
                    }
                }
            }
        }
    }
    // Check for negative-weight cycles , if so returns.
    for (size_t u = 0; u < numVertices; ++u) {
        for (size_t v = 0; v < numVertices; ++v) {
            if (graph.getAdjMatrix()[u][v] != 0) {
                int weight = graph.getAdjMatrix()[u][v];
                if (distances[u] != std::numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                    return "Graph contains a negative-weight cycle";
                }
            }
        }
    }

    if (distances[static_cast<size_t>(end)] == std::numeric_limits<int>::max()) {
        return "-1"; // No path found
    }

    std::vector<int> path;
    for (int at = end; at != -1; at = predecessors[static_cast<size_t>(at)]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    std::stringstream ss;
    for (std::size_t j = 0; j < path.size(); ++j) {
        ss << path[j];
        if (j < path.size() - 1) {
            ss << "->";
        }
    }
    return ss.str();
}

//Running DFS to check if theres a cycle by checking for back edges or if a vertex was already visited and finished.
bool Algorithms::dfsCheckCycle(const Graph& graph, size_t v, std::vector<bool>& visited, int parent) {
    visited[v] = true;
    for (std::size_t i = 0; i < static_cast<std::size_t>(graph.getNumVertices()); ++i) {
        if (graph.getAdjMatrix()[v][i] != 0) {
            if (!visited[i]) {
                if (dfsCheckCycle(graph, i, visited, v)) {
                    return true;
                }
            } else if (static_cast<int>(i) != parent) {
                std::cout << "The cycle is: " << v << "->" << i << "->" << parent << std::endl;
                return true;
            }
        }
    }
    return false;
}
// returns a boolean if theres a cycle , using the dfsCheckCycle.
bool Algorithms::isContainsCycle(const Graph& graph) {
    std::vector<bool> visited(graph.getNumVertices(), false);
    for (std::size_t i = 0; i < static_cast<std::size_t>(graph.getNumVertices()); ++i) {
        if (!visited[i]) {
            if (dfsCheckCycle(graph, i, visited, -1)) {
                return true;
            }
        }
    }
    return false;
}

bool Algorithms::isBipartiteUtil(const Graph& graph, size_t v, std::vector<int>& colors) {
    std::queue<int> q;
    q.push(v);
    colors[v] = 1;

    while (!q.empty()) {
        size_t u = static_cast<size_t>(q.front());
        q.pop();

        for (std::size_t i = 0; i < static_cast<std::size_t>(graph.getNumVertices()); ++i) {
            if (graph.getAdjMatrix()[u][i] != 0) {
                if (colors[i] == -1) {
                    colors[i] = 1 - colors[u];
                    q.push(static_cast<int>(i));
                } else if (colors[i] == colors[u]) {
                    return false;
                }
            }
        }
    }
    return true;
}
// checks if a graph is bipartite (can be colored in 2 colors) , using the function above that runs BFS
std::string Algorithms::isBipartite(const Graph& graph) {
    size_t numVertices = graph.getNumVertices();
    std::vector<int> colors(numVertices, -1);

    for (std::size_t i = 0; i < static_cast<std::size_t>(numVertices); ++i) {
        if (colors[i] == -1) {
            if (!isBipartiteUtil(graph, i, colors)) {
                return "0"; // Not bipartite
            }
        }
    }

    std::vector<int> setA, setB;
    for (std::size_t i = 0; i < static_cast<std::size_t>(numVertices); ++i) {
        if (colors[i] == 1) {
            setA.push_back(static_cast<int>(i));
        } else {
            setB.push_back(static_cast<int>(i));
        }
    }

    std::stringstream ss;
    ss << "The graph is bipartite: A={";
    for (std::size_t j = 0; j < setA.size(); ++j) {
        ss << setA[j];
        if (j < setA.size() - 1) {
            ss << ", ";
        }
    }
    ss << "}, B={";
    for (std::size_t j = 0; j < setB.size(); ++j) {
        ss << setB[j];
        if (j < setB.size() - 1) {
            ss << ", ";
        }
    }
    ss << "}";
    return ss.str();
}
//Bellman ford algorithm to check if theres a negative cycle - running on the V'th time to see any changes.
bool Algorithms::negativeCycle(const Graph& graph) {
    size_t numVertices = graph.getNumVertices();
    std::vector<int> distances(numVertices, std::numeric_limits<int>::max());

    distances[0] = 0;

    for (size_t k = 0; k < numVertices - 1; ++k) {
        for (size_t u = 0; u < numVertices; ++u) {
            for (size_t v = 0; v < numVertices; ++v) {
                if (graph.getAdjMatrix()[u][v] != 0) {
                    int weight = graph.getAdjMatrix()[u][v];
                    if (distances[u] != std::numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                        distances[v] = distances[u] + weight;
                    }
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (size_t u = 0; u < numVertices; ++u) {
        for (size_t v = 0; v < numVertices; ++v) {
            if (graph.getAdjMatrix()[u][v] != 0) {
                int weight = graph.getAdjMatrix()[u][v];
                if (distances[u] != std::numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                    return true; // Negative cycle found
                }
            }
        }
    }

    return false; // No negative cycle found
}


} // namespace ariel