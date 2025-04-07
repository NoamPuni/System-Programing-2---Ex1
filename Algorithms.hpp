// Algorithms.hpp
// noampuni99@gmail.com

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <iostream>
#include "Queue.hpp"
#include "Graph.hpp"
#include "PriorityQueue.hpp"

namespace graph {

class Algorithms {
private:
    // check if the graph is connected
    static bool isGraphConnected(Graph& graph);

    // Recursive function for DFS
    static void dfsRecursive(Graph& graph, int vertex, bool* visited, Graph& dfsTree);

    // Helper functions for Kruskal's algorithm: instead of using a union-find data structure
    static int find(int vertex, int* parent);

    static void union_sets(int u, int v, int* parent);

public:
    static Graph bfs(Graph& graph, int start);

    static Graph dfs(Graph& graph, int start);

    static Graph dijkstra(Graph& graph, int start);

    static Graph prim(Graph& graph);

    static Graph kruskal(Graph& graph);
};

} // namespace graph

#endif // ALGORITHMS_HPP