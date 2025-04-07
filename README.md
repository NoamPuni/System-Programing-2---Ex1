```markdown
# Graph Algorithms Project

## Overview
This project implements a modular and reusable graph data structure in C++, along with several classic graph algorithms. It supports undirected weighted graphs and includes traversal algorithms, shortest path finding, and minimum spanning tree (MST) construction.

## Features

### Implemented Algorithms
- **Breadth-First Search (BFS)** – Traverses the graph level by level and returns a BFS tree.
- **Depth-First Search (DFS)** – Explores as deep as possible before backtracking and returns a DFS tree.
- **Dijkstra's Algorithm** – Computes the shortest paths from a source vertex using a priority queue.
- **Prim's Algorithm** – Builds a MST starting from an arbitrary vertex.
- **Kruskal's Algorithm** – Builds a MST by sorting all edges by weight.

### Data Structures
- **Graph** – Implemented via adjacency lists for efficient edge access.
- **Queue** – Simple queue used in BFS.
- **Priority Queue** – Min-heap-based implementation used in Dijkstra and Prim algorithms.

## Project Structure
```
.
├── Algorithms.cpp       # Graph algorithms implementation
├── Algorithms.hpp       # Graph algorithms declarations
├── Graph.cpp            # Graph class implementation
├── Graph.hpp            # Graph class declarations
├── PriorityQueue.cpp    # Priority Queue implementation
├── PriorityQueue.hpp    # Priority Queue declarations
├── Queue.cpp            # Queue implementation
├── Queue.hpp            # Queue declarations
├── main.cpp             # Demonstration of functionality
├── test_graph.cpp       # Unit tests using doctest
└── Makefile             # Build and test automation
```

## Requirements
- **C++11 or later** – Uses features like smart pointers and range-based loops.
- **G++ Compiler** – Tested with GCC 13.3.0 (Ubuntu).
- **Valgrind** – For memory leak checks.
- **doctest** – Lightweight testing framework (embedded in `test_graph.cpp`).

## Building and Running

### Build the Project
```bash
make
```
Builds the main executable `ex1`.

### Run the Main Example
```bash
make Main
```
Builds and runs the main example demonstrating the graph algorithms.

### Run Unit Tests
```bash
make test
./test_graph
```
Runs unit tests with `doctest`.

### Check for Memory Leaks
```bash
make valgrind
```
Runs `ex1` with Valgrind (Valgrind must be installed).

### Clean Build Files
```bash
make clean
```
Removes all `.o` files and executables.

## Installation

1. Clone the repository:
```bash
git clone <repository-url>
cd CPP_EX1_25
```

2. Build the project:
```bash
make
```

3. Install Valgrind (if needed):
```bash
sudo apt update
sudo apt install valgrind
```

## Example Usage

```cpp
#include "Graph.hpp"
#include "Algorithms.hpp"
using namespace graph;

int main() {
    Graph graph(6);

    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 3, 3);
    graph.addEdge(3, 4, 1);

    Graph bfs_tree = Algorithms::bfs(graph, 0);
    std::cout << "BFS Tree:\n";
    bfs_tree.printGraph();

    Graph shortest_path = Algorithms::dijkstra(graph, 0);
    std::cout << "Shortest Path Tree:\n";
    shortest_path.printGraph();

    return 0;
}
```

## API Reference

### Graph Class
- `Graph(int vertices)` – Creates a graph with `vertices` nodes.
- `void addEdge(int src, int dest, int weight = 1)` – Adds an undirected edge.
- `void removeEdge(int src, int dest)` – Removes an edge, throws on error.
- `void printGraph()` – Prints the adjacency list.
- `int getVertices()` – Returns vertex count.
- `std::vector<Edge*>& getAdjacencyList(int vertex)` – Access adjacency list.

### Algorithms Class
- `Graph bfs(Graph& graph, int start)`
- `Graph dfs(Graph& graph, int start)`
- `Graph dijkstra(Graph& graph, int start)`
- `Graph prim(Graph& graph)`
- `Graph kruskal(Graph& graph)`

> All algorithms return new `Graph` objects. Exceptions are thrown for invalid inputs (e.g., negative weights in Dijkstra).

## Testing
Unit tests are in `test_graph.cpp` and run with:
```bash
make test
./test_graph
```

Tests cover:
- Graph operations (add/remove edges, validity).
- Algorithm correctness for BFS, DFS, Dijkstra, Prim, Kruskal.

## Notes
- Graphs are undirected (edges added both ways).
- Memory management is safe and handled using destructors.
- Valgrind recommended for memory leak checks.

## References
- AI-assisted planning and structure (e.g., project structure visualization, did not totally follow the suggestions).
- AI-based clarification regarding `.hpp` vs `.h`.
- AI-assisted README drafting.
- Summaries and Slides from:
  - **Data Structures** – Prof. Liad Gottlieb
  - **Algorithms 1** – Dr. Gabriel Nivasch
