//Specification file for Graph class
#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include<bits/stdc++.h>
#include <vector>
#include <list>
#include <utility>
using namespace std;

// Data structure to store a graph edge
struct Edge {
    int src, dest;
    float weight;
};
 
typedef pair<int, float> Pair;

class Graph{
private:
    bool isCyclicUtil(int v, bool visited[], bool *rs);  // used by isCyclic()
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;
    Graph(vector<Edge> const &edges, int n);   // Constructor
    void addEdge(int u, int v, int w);   // to add an edge to graph
    bool isCyclic();    // returns true if there is a cycle in this graph
    void displayGraph(Graph const &graph);
    ~Graph() { }
};

#endif