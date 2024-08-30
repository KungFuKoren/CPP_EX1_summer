#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
//  kkorenn1@gmail.com 209271535

using namespace std;

TEST_CASE("Test isConnected") {
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("Test shortestPath") {
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");
}

TEST_CASE("Test isContainsCycle") {
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == false);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == true);
}

TEST_CASE("Test isBipartite") {
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph3 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");
}

TEST_CASE("Test invalid graph") {
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));
}

TEST_CASE("Test empty graph") {
    ariel::Graph g;
    vector<vector<int>> graph = {};
    CHECK_THROWS(g.loadGraph(graph));
}

TEST_CASE("Test single vertex graph") {
    ariel::Graph g;
    vector<vector<int>> graph = {{0}};
    g.loadGraph(graph);
    CHECK(g.getNumVertices() == 0);
    CHECK(g.getNumEdges() == 0);
}

TEST_CASE("Test two connected vertices") {
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1},
        {1, 0}};
    g.loadGraph(graph);
    CHECK(g.getNumVertices() == 2);
    CHECK(g.getNumEdges() == 2);
}

TEST_CASE("Test two disconnected vertices") {
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 0},
        {0, 0}};
    g.loadGraph(graph);
    CHECK(g.getNumVertices() == 0);
    CHECK(g.getNumEdges() == 0);
}

TEST_CASE("Test symmetric matrix") {
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    g.loadGraph(graph);
    CHECK(g.getNumVertices() == 3);
    CHECK(g.getNumEdges() == 6);
}

TEST_CASE("Test non-symmetric matrix") {
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2},
        {1, 0, 2},
        {3, 4, 0}};
    CHECK_THROWS(g.loadGraph(graph));
}

TEST_CASE("Test addition of graphs") {
    ariel::Graph g1, g2;
    vector<vector<int>> graph1 = {
        {0, 1},
        {1, 0}};
    vector<vector<int>> graph2 = {
        {0, 2},
        {2, 0}};
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    ariel::Graph result = g1 + g2;
    CHECK(result.getAdjMatrix() == vector<vector<int>>{{0, 3}, {3, 0}});
}

TEST_CASE("Test subtraction of graphs") {
    ariel::Graph g1, g2;
    vector<vector<int>> graph1 = {
        {0, 3},
        {3, 0}};
    vector<vector<int>> graph2 = {
        {0, 1},
        {1, 0}};
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    ariel::Graph result = g1 - g2;
    CHECK(result.getAdjMatrix() == vector<vector<int>>{{0, 2}, {2, 0}});
}

TEST_CASE("Test multiplication by integer") {
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 2},
        {2, 0}};
    g.loadGraph(graph);
    ariel::Graph result = g.multByInt(3);
    CHECK(result.getAdjMatrix() == vector<vector<int>>{{0, 6}, {6, 0}});
}

TEST_CASE("Test division by integer") {
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 6},
        {6, 0}};
    g.loadGraph(graph);
    ariel::Graph result = g /= 2;
    CHECK(result.getAdjMatrix() == vector<vector<int>>{{0, 3}, {3, 0}});
}

TEST_CASE("Test increment operator") {
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1},
        {1, 0}};
    g.loadGraph(graph);
    ++g;
    CHECK(g.getAdjMatrix() == vector<vector<int>>{{0, 2}, {2, 0}});
}

TEST_CASE("Test decrement operator") {
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 2},
        {2, 0}};
    g.loadGraph(graph);
    --g;
    CHECK(g.getAdjMatrix() == vector<vector<int>>{{0, 1}, {1, 0}});
}

TEST_CASE("Test equality operator") {
    ariel::Graph g1, g2;
    vector<vector<int>> graph = {
        {0, 1},
        {1, 0}};
    g1.loadGraph(graph);
    g2.loadGraph(graph);
    CHECK(g1 == g2);
}

