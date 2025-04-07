#ifndef GRAPH_HPP
#define GRAPH_HPP

namespace graph {

struct Edge {
    int dest;
    int weight;
    Edge* next;
};

class Graph {
private:
    const int vertices;
    Edge** adjacencyList;

    void removeEdge2(int src, int dest); // helper function
public:
    // Constructor
    Graph(int vertices);

    // Destructor
    ~Graph();

    // Add an edge to the graph
    void addEdge(int src, int dest, int weight = 1); // Default weight is 1

    // Remove an edge from the graph
    void removeEdge(int src, int dest);

    // Print the graph
    void printGraph();

    int getVertices() const;  

    Edge** getAdjacencyList(int vertex);
};

} // namespace graph

#endif // GRAPH_HPP
