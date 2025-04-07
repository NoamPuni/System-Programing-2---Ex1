#include <iostream>
#include "Graph.hpp"
#include "Algorithms.hpp"
using namespace graph;
int main() {
    // build a graph
    Graph graph(6);

    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 3);
    graph.addEdge(2, 3, 3);
    graph.addEdge(2, 4, 2);
    graph.addEdge(3, 4, 3);
    graph.addEdge(3, 5, 2);
    graph.addEdge(4, 5, 3);

    // BFS
    Graph bfs_tree = Algorithms::bfs(graph, 0);
    std::cout << "\nBFS Tree:" << std::endl;
    bfs_tree.printGraph();

    // DFS
    Graph dfs_tree = Algorithms::dfs(graph, 0);
    std::cout << "\nDFS Tree:" << std::endl;
    dfs_tree.printGraph();

    // Dijkstra
    Graph dijkstra_tree = Algorithms::dijkstra(graph, 0);
    std::cout << "\nDijkstra Tree:" << std::endl;
    dijkstra_tree.printGraph();

    // Prim
    Graph prim_mst = Algorithms::prim(graph);
    std::cout << "\nPrim MST:" << std::endl;
    prim_mst.printGraph();

    // Kruskal
    Graph kruskal_mst = Algorithms::kruskal(graph);
    std::cout << "\nKruskal MST:" << std::endl;
    kruskal_mst.printGraph();

    // edge removal
    //std::cout << "\nRemoving edge (0, 1) from the graph." << std::endl;
    graph.removeEdge(0, 1);

    // print the graph after removing an edge
    std::cout << "\nGraph after removing edge (0, 1):" << std::endl;
    graph.printGraph();

    return 0;
}