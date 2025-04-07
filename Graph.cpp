#include "Graph.hpp"
#include <iostream>

namespace graph {

    // עזר להסרה חד-כיוונית
    void Graph::removeEdge2(int src, int dest) {
        Edge* current = adjacencyList[src];// Get the first edge
        Edge* previous = nullptr;// Get the previous edge

        while (current != nullptr) {// While there are still edges
            if (current->dest == dest) {// If the edge is found
                if (previous == nullptr) {// If the edge is the first edge
                    adjacencyList[src] = current->next;// Move to the next edge
                } else {
                    previous->next = current->next;// Move to the next edge
                }
                delete current;// Delete the edge
                return;
            }
            previous = current;// Save the current edge
            current = current->next;// Move to the next edge
        }

        throw std::invalid_argument("edge is not found");// If the edge is not found
    }

    // Constructor
    Graph::Graph(int vertices) : vertices(vertices) { // Initialize the adjacency list
        adjacencyList = new Edge*[vertices];// Create a new array of pointers to edges
        for (int i = 0; i < vertices; ++i) { // For each vertex
            adjacencyList[i] = nullptr;// Initialize each pointer to nullptr
        }
    }

    // Destructor //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ MEMORY LEAK VALGRIND
    Graph::~Graph() {
        for (int i = 0; i < vertices; ++i) { // For each vertex
            Edge* current = adjacencyList[i]; // Get the current edge
            while (current != nullptr) { // While there are still edges
                Edge* temp = current; // Save the current edge
                current = current->next; // Move to the next edge
                delete temp;// Delete the saved edge
            }
        }
        delete[] adjacencyList;// Delete the array of pointers to edges
    }

    void Graph::addEdge(int src, int dest, int weight) { 
        if (src < 0 || src >= vertices || dest < 0 || dest >= vertices) {
            std::cerr << "Invalid vertex\n"; // Check if the vertex is valid
            return;
        }

        Edge* current = adjacencyList[src];
        while (current != nullptr) {
            if (current->dest == dest) {
                std::cerr << "Edge already exists"; // Check if the edge already exists
                return;
            }
            current = current->next;
        }

        Edge* newEdgeS2D = new Edge{dest, weight, adjacencyList[src]}; //Create a new edge src->dest
        adjacencyList[src] = newEdgeS2D; // Add the edge to the adjacency list
        Edge* newEdgeD2S = new Edge{src, weight, adjacencyList[dest]}; // Create a new edge dest->src
        adjacencyList[dest] = newEdgeD2S; // Add the edge to the adjacency list 
    }

    void Graph::removeEdge(int src, int dest){
        if (src < 0 || src >= vertices || dest < 0 || dest >= vertices) {
            throw std::invalid_argument("Invalid vertex\n");// Check if the vertex is valid
        }
        removeEdge2(src, dest);// Remove the edge src->dest
        removeEdge2(dest, src);// Remove the edge dest->src
    }

    void Graph::printGraph() { 
        //format: "adjacency list of vertex i -- (weight) --> dest -- (weight) --> dest -- END"

        // create a 2D array to keep track of printed edges to avoid printing the same edge twice
        bool** printedEdges = new bool*[vertices];
        for (int i = 0; i < vertices; ++i) {
            printedEdges[i] = new bool[vertices];
            for (int j = 0; j < vertices; ++j) {
                printedEdges[i][j] = false;//i-source, j-destination
            }
        }

        for (int i = 0; i < vertices; ++i) {
            std::cout <<"adjacency list of vertex " << i << " -- "; // print the source vertex
            Edge* current = adjacencyList[i];// get the first edge
            while (current != nullptr) {
                int dest = current->dest;// get the destination vertex
                int weight = current->weight;// get the weight of the edge

                // make sure the edge is not printed before
                if (!printedEdges[i][dest] && !printedEdges[dest][i]) {
                    std::cout << "(" << weight << ") --> " << dest << " -- "; // print the edge
                    printedEdges[i][dest] = true; // mark the edge as printed
                }
                current = current->next;// move to the next edge
            }
            std::cout << "END" << std::endl; // end of the adjacency list
        }

        // free the memory allocated for the 2D array
        for (int i = 0; i < vertices; ++i) {
            delete[] printedEdges[i];
        }
        delete[] printedEdges;
    }

    int Graph::getVertices() const {
        return vertices;
    }

    Edge** Graph::getAdjacencyList(int vertex) {
        return &adjacencyList[vertex];
    }

} // namespace graph
