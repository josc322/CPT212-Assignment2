//Specification file for Graph class
#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include<bits/stdc++.h>
#include <vector>
#include <list>
#include <utility>
using namespace std;

/// Data structure to store a graph edge
struct Edge {
    int src, dest, weight;
};
 
typedef pair<int, int> Pair;

class Graph{
    bool isCyclicUtil(Graph &graph, int a, bool visited[], bool *rs);  // used by isCyclic()
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;
    Graph(vector<Edge> &edges, int n);   // Constructor
    void addEdge(Graph &graph, int u, int v);   // to add an edge to graph
    bool edgeExists(Graph &graph, int u, int v); //check if edge exists
    bool isCyclic(Graph &graph);    // returns true if there is a cycle in this graph
    void displayGraph(Graph &graph);
    ~Graph() { }
};

#endif
