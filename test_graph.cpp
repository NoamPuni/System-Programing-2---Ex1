#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Graph.hpp"
#include "Algorithms.hpp"
#include "Queue.hpp"
#include "PriorityQueue.hpp"
#include <iostream>

using namespace graph;

// Tests for Graph class
TEST_CASE("Graph class - addEdge") {
    SUBCASE("Test 1: Adding a regular edge") {
        Graph g(3); // Graph with 3 vertices
        g.addEdge(0, 1, 1); // Add an edge between 0 and 1 with weight 1
        Edge* edge01 = g.getAdjacencyList(0)[0];
        Edge* edge10 = g.getAdjacencyList(1)[0];
        CHECK(edge01 != nullptr); // Check that 0 knows 1
        CHECK(edge01->dest == 1);
        CHECK(edge01->weight == 1);
        CHECK(edge10 != nullptr); // Check that 1 knows 0 (undirected graph)
        CHECK(edge10->dest == 0);
        CHECK(edge10->weight == 1);
    }

    SUBCASE("Test 2: Adding an edge twice") {
        Graph g(3);
        g.addEdge(0, 1, 1); // Add first edge
        g.addEdge(0, 1, 1); // Try adding it again
        Edge* edge = g.getAdjacencyList(0)[0];
        CHECK(edge != nullptr);
        CHECK(edge->dest == 1);
        CHECK(edge->next == nullptr); // Check that there are no duplicate edges
    }

    SUBCASE("Test 3: Edge with invalid vertex") {
        Graph g(3);
        CHECK_THROWS_AS(g.addEdge(-1, 0, 1), std::invalid_argument); // Negative vertex
        CHECK_THROWS_AS(g.addEdge(0, 3, 1), std::invalid_argument); // Vertex out of range
    }
}

TEST_CASE("Graph class - removeEdge") {
    SUBCASE("Test 1: Removing an existing edge") {
        Graph g(3);
        g.addEdge(0, 1, 1);
        g.removeEdge(0, 1);
        CHECK(g.getAdjacencyList(0)[0] == nullptr); // Check that 0 is not connected to 1
        CHECK(g.getAdjacencyList(1)[0] == nullptr); // Check that 1 is not connected to 0
    }

    SUBCASE("Test 2: Removing a non-existent edge") {
        Graph g(3);
        CHECK_THROWS_AS(g.removeEdge(0, 2), std::invalid_argument); // Try removing an edge that doesn't exist
    }
}

// Tests for Algorithms class
TEST_CASE("Algorithms class - bfs") {
    SUBCASE("Test 1: Simple BFS tree") {
        Graph g(4);
        g.addEdge(0, 1, 1);
        g.addEdge(0, 2, 1);
        g.addEdge(1, 3, 1);
        Graph bfsTree = Algorithms::bfs(g, 0);
        CHECK(bfsTree.getVertices() == 4); // Check that the number of vertices is correct
        int edgeCount = 0;
        for (int i = 0; i < 4; ++i) {
            Edge* e = bfsTree.getAdjacencyList(i)[0];
            while (e != nullptr) {
                edgeCount++;
                e = e->next;
            }
        }
        CHECK(edgeCount / 2 == 3); // N-1 edges (since each edge is counted twice in an undirected graph)
        CHECK(bfsTree.getAdjacencyList(0) != nullptr); // Check that all vertices are reachable
        CHECK(bfsTree.getAdjacencyList(1) != nullptr);
        CHECK(bfsTree.getAdjacencyList(2) != nullptr);
        CHECK(bfsTree.getAdjacencyList(3) != nullptr);
    }

    SUBCASE("Test 2: Non-existent vertex") {
        Graph g(4);
        CHECK_THROWS_AS(Algorithms::bfs(g, -1), std::invalid_argument); // Negative vertex
        CHECK_THROWS_AS(Algorithms::bfs(g, 4), std::invalid_argument); // Vertex out of range
    }

    SUBCASE("Test 3: Disconnected graph") {
        Graph g(4);
        g.addEdge(0, 1, 1); // Component 1: 0-1
        g.addEdge(2, 3, 1); // Component 2: 2-3
        Graph bfsTree = Algorithms::bfs(g, 0);
        CHECK(bfsTree.getAdjacencyList(0) != nullptr); // Component of 0 exists
        CHECK(bfsTree.getAdjacencyList(1) != nullptr);
        CHECK(bfsTree.getAdjacencyList(2)[0] == nullptr); // 2 and 3 are not reachable from 0
        CHECK(bfsTree.getAdjacencyList(3)[0] == nullptr);
    }
}

TEST_CASE("Algorithms class - dijkstra") {
    SUBCASE("Test 1: Shortest path") {
        Graph g(3);
        g.addEdge(0, 1, 2);
        g.addEdge(1, 2, 3);
        g.addEdge(0, 2, 6); // Direct but longer path
        Graph dijkstraTree = Algorithms::dijkstra(g, 0);
        Edge* e01 = dijkstraTree.getAdjacencyList(0)[0];
        Edge* e12 = dijkstraTree.getAdjacencyList(1)[0];
        CHECK(e01 != nullptr);
        CHECK(e01->dest == 1);
        CHECK(e01->weight == 2);
        CHECK(e12 != nullptr);
        CHECK(e12->dest == 2);
        CHECK(e12->weight == 3); // Total weight from 0 to 2 is 5 via 1
    }

    SUBCASE("Test 2: Edge with negative weight") {
        Graph g(3);
        g.addEdge(0, 1, -1); // Negative weight
        CHECK_THROWS_AS(Algorithms::dijkstra(g, 0), std::invalid_argument);
    }

    SUBCASE("Test 3: Non-existent vertex") {
        Graph g(3);
        CHECK_THROWS_AS(Algorithms::dijkstra(g, -1), std::invalid_argument);
        CHECK_THROWS_AS(Algorithms::dijkstra(g, 3), std::invalid_argument);
    }
}

TEST_CASE("Algorithms class - prim") {
    SUBCASE("Test 1: Minimum spanning tree") {
        Graph g(4);
        g.addEdge(0, 1, 4);
        g.addEdge(0, 2, 1);
        g.addEdge(1, 2, 2);
        g.addEdge(1, 3, 5);
        g.addEdge(2, 3, 3);
        Graph primTree = Algorithms::prim(g);
        CHECK(primTree.getVertices() == 4);
        int edgeCount = 0;
        int totalWeight = 0;
        for (int i = 0; i < 4; ++i) {
            Edge* e = primTree.getAdjacencyList(i)[0];
            while (e != nullptr) {
                edgeCount++;
                totalWeight += e->weight;
                e = e->next;
            }
        }
        CHECK(edgeCount / 2 == 3); // N-1 edges
        CHECK(totalWeight / 2 == 6); // Minimum weight: 1 (0-2) + 2 (1-2) + 3 (2-3)
    }

    SUBCASE("Test 2: Disconnected graph") {
        Graph g(4);
        g.addEdge(0, 1, 1); // Component 1
        g.addEdge(2, 3, 1); // Component 2
        CHECK_THROWS_AS(Algorithms::prim(g), std::invalid_argument);
    }
}

TEST_CASE("Algorithms class - kruskal") {
    SUBCASE("Test 1: Minimum spanning tree") {
        Graph g(4);
        g.addEdge(0, 1, 4);
        g.addEdge(0, 2, 1);
        g.addEdge(1, 2, 2);
        g.addEdge(1, 3, 5);
        g.addEdge(2, 3, 3);
        Graph kruskalTree = Algorithms::kruskal(g);
        CHECK(kruskalTree.getVertices() == 4);
        int edgeCount = 0;
        int totalWeight = 0;
        for (int i = 0; i < 4; ++i) {
            Edge* e = kruskalTree.getAdjacencyList(i)[0];
            while (e != nullptr) {
                edgeCount++;
                totalWeight += e->weight;
                e = e->next;
            }
        }
        CHECK(edgeCount / 2 == 3); // N-1 edges
        CHECK(totalWeight / 2 == 6); // Minimum weight: 1 (0-2) + 2 (1-2) + 3 (2-3)
    }

    SUBCASE("Test 2: Disconnected graph") {
        Graph g(4);
        g.addEdge(0, 1, 1); // Component 1
        g.addEdge(2, 3, 1); // Component 2
        CHECK_THROWS_AS(Algorithms::kruskal(g), std::invalid_argument);
    }
}