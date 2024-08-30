#ifndef GRAPH_HPP
#define GRAPH_HPP
//  kkorenn1@gmail.com 209271535
#include <unordered_set>
#include <vector>
#include <stdexcept>
#include <iostream>

namespace ariel {

class Graph {
public:
    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);



    bool operator==(const Graph &toAdd) const;
    bool operator<=(const Graph &toAdd) const;
    bool operator>=(const Graph &toAdd) const;
    bool operator<(const Graph &toAdd) const;    
    bool operator>(const Graph &toAdd) const;    
    bool operator!=(const Graph &toAdd) const;

    friend Graph operator*(const Graph &toAdd, const Graph &toAdd2);
    friend Graph operator+(const Graph &toAdd, const Graph &toAdd2);
    Graph operator*(int scalar);
    Graph operator++();
    Graph operator--();
    Graph operator-() const;
    Graph operator+() const;    
    Graph operator-=(const Graph &toAdd);
    Graph operator-(const Graph &toAdd) const;
    Graph operator*=(int mult);
    Graph operator/=(int mult);
    Graph operator+=(const Graph &toAdd);

    void isSameSize(const Graph &g) const;
    void canBeContained(const Graph &g) const;
    void canIBeContained(const Graph &g) const;
    void loadGraph(const std::vector<std::vector<int>>& matrix);
    void loadGraph2(const std::vector<std::vector<int>>& matrix);
    Graph multByInt(int a);
    void printGraph() const;
    size_t getNumVertices() const;
    int getNumEdges() const;
    const std::vector<std::vector<int>>& getAdjMatrix() const;

private:
    std::vector<std::vector<int>> adjMatrix;
    size_t numVertices = 0;
};

} // namespace ariel

#endif // GRAPH_HPP