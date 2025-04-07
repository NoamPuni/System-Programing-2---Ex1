# Graph Algorithms Library

## Overview
This library implements a graph data structure and several fundamental graph algorithms in C++. It provides an efficient implementation of undirected weighted graphs and includes algorithms for traversal, shortest paths, and minimum spanning tree construction.

## Algorithms Implemented
- **Breadth-First Search (BFS)**: Traverses the graph level by level
- **Depth-First Search (DFS)**: Traverses the graph by exploring as far as possible along each branch
- **Dijkstra's Algorithm**: Finds the shortest path from a source vertex to all other vertices
- **Prim's Algorithm**: Constructs a minimum spanning tree starting from an arbitrary vertex
- **Kruskal's Algorithm**: Constructs a minimum spanning tree by considering edges in ascending order of weight

## Data Structures
The project includes implementations of the following data structures:
- **Graph**: Represented using adjacency lists
- **Queue**: Used for BFS implementation
- **Priority Queue**: Used for Dijkstra's and Prim's algorithms

## Project Structure
```
.
├── Algorithms.cpp       # Implementation of graph algorithms
├── Algorithms.hpp       # Header for graph algorithms
├── Graph.cpp            # Implementation of the graph data structure
├── Graph.hpp            # Header for the graph data structure
├── PriorityQueue.cpp    # Implementation of priority queue
├── PriorityQueue.hpp    # Header for priority queue
├── Queue.cpp            # Implementation of queue
├── Queue.hpp            # Header for queue
├── main.cpp             # Example usage
├── test_graph.cpp       # Unit tests
└── Makefile             # Build instructions
```

## Requirements
- C++11 or later
- G++ compiler
- Valgrind (optional, for memory leak detection)

## Building and Running
The project includes a Makefile with several targets:

### Build the Project
```bash
make
```

### Run the Main Example
```bash
make Main
```

### Run Tests
```bash
make test
./test_graph
```

### Check for Memory Leaks
```bash
make valgrind
```

### Clean Build Files
```bash
make clean
```

## Example Usage
```cpp
#include "Graph.hpp"
#include "Algorithms.hpp"
using namespace graph;

int main() {
    // Create a graph with 6 vertices
    Graph graph(6);

    // Add edges (src, dest, weight)
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 2);
    // Add more edges...

    // Run BFS from vertex 0
    Graph bfs_tree = Algorithms::bfs(graph, 0);
    
    // Print the resulting tree
    bfs_tree.printGraph();
    
    return 0;
}
```

## API Reference

### Graph Class
- `Graph(int vertices)`: Constructor to create a graph with specified number of vertices
- `addEdge(int src, int dest, int weight = 1)`: Add an edge between src and dest vertices with given weight
- `removeEdge(int src, int dest)`: Remove the edge between src and dest vertices
- `printGraph()`: Print the adjacency list representation of the graph
- `getVertices()`: Get the number of vertices in the graph
- `getAdjacencyList(int vertex)`: Get the adjacency list of a specific vertex

### Algorithms Class
- `bfs(Graph& graph, int start)`: Run BFS starting from the specified vertex
- `dfs(Graph& graph, int start)`: Run DFS starting from the specified vertex
- `dijkstra(Graph& graph, int start)`: Run Dijkstra's algorithm from the specified vertex
- `prim(Graph& graph)`: Run Prim's algorithm to find a minimum spanning tree
- `kruskal(Graph& graph)`: Run Kruskal's algorithm to find a minimum spanning tree

## Notes
- All algorithms return a new Graph representing the result (e.g., shortest path tree, spanning tree)
- The implementation handles error cases such as disconnected graphs or invalid vertices
- The graph implementation is undirected - each edge is added in both directions