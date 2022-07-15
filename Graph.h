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
    bool hasCycleUtil(Graph &graph, int a, bool visited[], bool *rs, vector<int> &path);  // used by hasCycle()
    void DFSUtil(Graph &graph, int v, bool visited[]); //used by isSC() 
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;
    Graph(vector<Edge> &edges, int n);   // Constructor
    void addEdge(Graph &graph, int u, int v);   // to add an edge to graph
    void removeEdge(Graph &graph, int u, int v); //remove edge from graph
    bool edgeExists(Graph &graph, int u, int v); //check if edge exists
    bool hasCycle(Graph &graph, vector<int> &path);    // returns true if there is a cycle in this graph
    void displayGraph(Graph &graph); //display graph
    void countEdges(Graph const &graph); // count the number of edges in the graph
    bool isSC(Graph &graph); //returns true if there are strong connection between graph
    void getReverse(Graph &graph); //for bool isSC
    void PrimsAlgorithm(int n, vector<vector<Pair>> adjList); // Find the MST of the graph
    void clearGraph(Graph &g); // clear the graph
	
	
    ~Graph() { } //Destructor
};

#endif
