//noampuni99@gmail.com
#include <iostream>
#include "Queue.hpp" 
#include "Graph.hpp" 
#include "PriorityQueue.hpp"
#include "Algorithms.hpp"
//using namespace graph;
namespace graph {
    
        // check if the graph is connected
        bool Algorithms::isGraphConnected(Graph& graph) {
            int vertices = graph.getVertices();
            // empty graph is not needed to check

            // running BFS from a arbitrary vertex (0)
            Graph bfsTree = bfs(graph, 0);
            for (int i = 0; i < vertices; ++i) { // check if all vertices got visited
                if (bfsTree.getAdjacencyList(i) == nullptr) {
                    return false; // there is at least one vertex that is not connected
                }
            }
            return true; 
        }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Recursive function for DFS
        void Algorithms::dfsRecursive(Graph& graph, int vertex, bool* visited, Graph& dfsTree) {
            visited[vertex] = true; // Mark the current vertex as visited

            // Get the adjacency list of the current vertex
            Edge* currentEdge = graph.getAdjacencyList(vertex)[0]; // Get the first edge of the current vertex

            while (currentEdge != nullptr) { // While there are edges to explore
                int neighbor = currentEdge->dest; // Get the destination vertex of the edge 

                // If the neighbor vertex is not visited, add it to the DFS tree and call DFS recursively
                if (!visited[neighbor]) {
                    dfsTree.addEdge(vertex, neighbor, currentEdge->weight); // Add edge to DFS tree
                    dfsRecursive(graph, neighbor, visited, dfsTree); // Recursive call
                }

                currentEdge = currentEdge->next; // Move to the next edge
            }
        }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Helper functions for Kruskal's algorithm: instead of using a union-find data structure
        int Algorithms::find(int vertex, int* parent) { // finding the representative of a vertices group
            while (parent[vertex] != vertex) { // while the vertex is not its own parent
                vertex = parent[vertex];// update the vertex to its parent
            }
            return vertex; // the representative of the group
        }
    /////////////////////////////////////////////////////////////////////////////////////////////
         void Algorithms::union_sets(int u, int v, int* parent) { // unite two groups of vertices
            int rootU = find(u, parent); // find the representative of u
            int rootV = find(v, parent); // find the representative of v
            parent[rootU] = rootV; // unite the two groups by making one representative the parent of the other
        }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

         Graph Algorithms::bfs(Graph& graph, int start) {
            int vertices = graph.getVertices();

            // check if it's a valid graph and start vertex
            if (start < 0 || start >= vertices) {
                throw std::invalid_argument("start vertex is out of range");
            }
            if (vertices == 0) {
                throw std::invalid_argument("graph is empty");
            }

            // save status of vertices (visited or not)
            bool* visited = new bool[vertices];
            for (int i = 0; i < vertices; ++i) {
                visited[i] = false;
            }

            // a queue for vertices who wait to be visited
            Queue queue; // Create a queue for BFS

            // new graph for BFS tree
            Graph bfsTree(vertices);

            // start BFS from the start vertex
            visited[start] = true;
            queue.push(start);

            while (!queue.isEmpty()) {
                int current = queue.pop(); // Get and remove the first element from the queue

                // run through all edges of the current vertex and add them to the BFS tree
                Edge* currentEdge = graph.getAdjacencyList(current)[0]; // Get the first edge of the current vertex
                while (currentEdge != nullptr) { // Get the next edge
                    int neighbor = currentEdge->dest; // Get the destination vertex of the edge 

                    // if the neighbor vertex is not visited, add it to the queue and mark it as visited
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        queue.push(neighbor);
                        bfsTree.addEdge(current, neighbor, currentEdge->weight);
                    }

                    currentEdge = currentEdge->next;// Get the next edge
                }
            }
            delete[] visited;
            return bfsTree;
        }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
         Graph Algorithms::dfs(Graph& graph, int start) {
            int vertices = graph.getVertices();

            //check if it's a valid graph and start vertex
            if (start < 0 || start >= vertices) {
                throw std::invalid_argument("start vertex is out of range");
            }
            if (vertices == 0) {
                throw std::invalid_argument("graph is empty");
            }

            // save status of vertices (visited or not)
            bool* visited = new bool[vertices];
            for (int i = 0; i < vertices; ++i) {
                visited[i] = false;
            }

            // new graph for DFS tree
            Graph dfsTree(vertices);

            // recursive DFS function
            dfsRecursive(graph, start, visited, dfsTree);
            delete[] visited;
            return dfsTree;
        }
/////////////////////////////////////////////////////////////////////////////////////////////////////////
         Graph Algorithms::dijkstra(Graph& graph, int start) {
            int vertices = graph.getVertices();
            // check if it's a valid graph and start vertex
            if (start < 0 || start >= vertices) {
                throw std::invalid_argument("start vertex is out of range");
            }
            if (vertices == 0) {
                throw std::invalid_argument("graph is empty");
            }
            // check for negative weights
            for (int i = 0; i < vertices; ++i) {
                Edge* currentEdge = graph.getAdjacencyList(i)[0];
                while (currentEdge != nullptr) {
                    if (currentEdge->weight < 0) {
                        throw std::invalid_argument("cant use Dijkstra algorithm with negative weights");
                    }
                    currentEdge = currentEdge->next;
                }
            }
            int* distance = new int[vertices]; // an array to save the distance from the start vertex to every vertex
            int* parent = new int[vertices];// an array to save the parent of every vertex in the shortest path tree
            int infinity = 1000000000; // the biggest power of 10 possible to represent infinity
            for (int i = 0; i < vertices; ++i) {
                distance[i] = infinity; // initialize all distances to infinity
                parent[i] = -1; // initialize all parents to -1 (no parent)
            }
            distance[start] = 0;// set the distance of the start vertex to 0           
            PriorityQueue pq(vertices);
            pq.push(start, 0); // add the start vertex to the priority queue with distance 0    
            while (!pq.isEmpty()) {
                int current = pq.pop();// get the vertex with the smallest distance from the priority queue    
                Edge* currentEdge = graph.getAdjacencyList(current)[0];
                while (currentEdge != nullptr) {
                    int neighbor = currentEdge->dest;
                    int weight = currentEdge->weight;
    
                    // if the distance to the neighbor vertex is smaller than the current distance, update it
                    // and add it to the priority queue
                    if (distance[current] + weight < distance[neighbor]) {
                        distance[neighbor] = distance[current] + weight;
                        parent[neighbor] = current;// set the parent of the neighbor vertex to the current vertex
                        pq.push(neighbor, distance[neighbor]);
                    }
                    currentEdge = currentEdge->next;
                }
            }  
            // create new graph for the shortest path tree
            Graph shortestPathTree(vertices);// the new gragh has the same number of vertices as the original graph
            for (int i = 0; i < vertices; ++i) {
                if (i != start) {
                    shortestPathTree.addEdge(parent[i], i, distance[i] - distance[parent[i]]);
                }//add the edges to the tree with the weight of each the edge
            }
            delete[] distance;
            delete[] parent;
    
            return shortestPathTree;
        }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         Graph Algorithms::prim(Graph& graph) {
            int vertices = graph.getVertices();

            // check if it's a valid graph to apply Prim's algorithm
            if (vertices == 0) {
                throw std::invalid_argument("graph is empty");
            }

            // check if the graph is connected
            if (!isGraphConnected(graph)) {
                throw std::invalid_argument("graph is not connected");
            }
            // arrays to save the details of vertices
            bool* visited = new bool[vertices];// array to save the visited status of vertices
            int* parent = new int[vertices];// array to save the parent of each vertex in the MST
            int* key = new int[vertices]; // array to save the minimum weights
            int infinity = 1000000000; // the biggest power of 10 possible to represent infinity
            for (int i = 0; i < vertices; ++i) {// initialize all vertices' details
                visited[i] = false;
                key[i] = infinity;
                parent[i] = -1;
            }
            // starting vertex (arbitrary choice)
            int start = 0;
            key[start] = 0; // set the key of the starting vertex to 0
            PriorityQueue pq(vertices);
            pq.push(start, 0); // add the starting vertex to the priority queue with key 0
            while (!pq.isEmpty()) {
                int current = pq.pop();// get the vertex with the smallest key from the priority queue
                if (visited[current]) continue; // if the vertex is already visited, skip it
                visited[current] = true; // mark the current vertex as visited
                // run through all edges of the current vertex and update the keys of its neighbors
                Edge* currentEdge = graph.getAdjacencyList(current)[0]; // ge the adjacency list of the current vertex
                while (currentEdge != nullptr) {// while there are edges to explore
                    int neighbor = currentEdge->dest;
                    int weight = currentEdge->weight;
                    //if the neighbor vertex is not visited and the weight is smaller than the current key
                    if (!visited[neighbor] && weight < key[neighbor]) {
                        key[neighbor] = weight;// update the key of the neighbor vertex
                        parent[neighbor] = current;// set the parent of the neighbor vertex to the current vertex
                        // add the neighbor vertex to the priority queue with the new key
                        pq.push(neighbor, key[neighbor]);
                    }
                    currentEdge = currentEdge->next;
                }
            }
        
            Graph mst(vertices);//build the new minimum spaninng tree
            for (int i = 0; i < vertices; ++i) {
                if (parent[i] != -1) {
                    mst.addEdge(parent[i], i, key[i]);
                }
            }
            delete[] visited;
            delete[] parent;
            delete[] key;
            return mst;
        }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     Graph Algorithms::kruskal(Graph& graph) {
        int vertices = graph.getVertices();
        // check if it's a valid graph to apply Kruskal's algorithm
        if (vertices == 0) {
            throw std::invalid_argument("graph is empty");
        }
        // check if the graph is connected
        if (!isGraphConnected(graph)) {
            throw std::invalid_argument("graph is not connected");
        }
        int edgeCount = 0;
        for (int i = 0; i < vertices; ++i) {//for each edge in the graph
            Edge* currentEdge = graph.getAdjacencyList(i)[0];
            while (currentEdge != nullptr) {
                edgeCount++;//update the number of edges
                currentEdge = currentEdge->next;
            }
        }
        if (edgeCount / 2 < vertices - 1) { //check if the num of edges is less than the num of vertices-1
            throw std::invalid_argument("not enough edges to find MST"); 
        }

        // sorting the edges
        int maxEdges = edgeCount / 2; // because the graph is undirected, each edge is counted twice
        int** edges = new int*[maxEdges]; // an 2D array to save the edges
        for (int i = 0; i < maxEdges; ++i) {
            edges[i] = new int[3];//each edge has 3 values: [0]:src, [1]dest, [2]weight
        }
        int edgeIndex = 0; // index for the edges array
        for (int i = 0; i < vertices; ++i) { //for each edge in the graph
            Edge* currentEdge = graph.getAdjacencyList(i)[0]; 
            while (currentEdge != nullptr) { 
                if (i < currentEdge->dest) { // to avoid duplicates, only add edges in one direction
                    edges[edgeIndex][0] = i; // src vertex
                    edges[edgeIndex][1] = currentEdge->dest; // dest vertex
                    edges[edgeIndex][2] = currentEdge->weight; // edge weight
                    edgeIndex++; // increment the edge index
                }
                currentEdge = currentEdge->next; // move to the next edge
            }
        }
        


        // Sort the edges based on their weights using a simple bubble sort 
        for (int i = 0; i < edgeIndex - 1; ++i) {
            for (int j = 0; j < edgeIndex - i - 1; ++j) {
                if (edges[j][2] > edges[j + 1][2]) { // compare weights
                    // swap edges
                    int* temp = edges[j];
                    edges[j] = edges[j + 1];
                    edges[j + 1] = temp;
                }
            }
        }

        int* parent = new int[vertices]; // create an array to keep track of the parent of each vertex
        for (int i = 0; i < vertices; ++i) {
            parent[i] = i; // initialize each vertex as its own parent
        }

        //build the MST from the sorted edges
        Graph mst(vertices); // creates new graph for the MST
        int addedEdges = 0; // counter for the number of edges added to the MST
        for (int i = 0; i < edgeIndex; ++i) { // run through all sorted edges
            int u = edges[i][0]; // u:= src vertex
            int v = edges[i][1]; // v:= dest vertex
            int weight = edges[i][2]; // weight of the edge

            if (find(u, parent) != find(v, parent)) { // check if u and v are in different sets
                mst.addEdge(u, v, weight); // add the edge to the MST
                union_sets(u, v, parent); // union the sets of u and v
                addedEdges++; 
            }
        }

        // final check: if the number of edges in the MST is not equal to vertices - 1, something went wrong
        if (addedEdges != vertices - 1) {
            throw std::runtime_error("MST building failed: wrong number of edges added");
        }

        // clean memory
        for (int i = 0; i < maxEdges; ++i) {
            delete[] edges[i];
        }
        delete[] edges;
        delete[] parent;
        return mst;
    }
};// namespace graph
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
