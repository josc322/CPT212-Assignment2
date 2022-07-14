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
    Edge(int start,  int end, int w) {
        src = start;
        dest = end;
        weight = w;
    }
};

struct Node {
    unordered_map<int, Edge*> edgesComingIn;
    unordered_map<int, Edge*> edgesGoingOut;
    Edge* edgeInMDST;
};

typedef pair<int, int> Pair;

class Graph{
    bool hasCycleUtil(Graph &graph, int a, bool visited[], bool *rs, vector<int> &path);  // used by hasCycle()
    void DFSUtil(Graph &graph, int v, bool visited[]); //used by isSC() 
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;
    vector<Node*> nodes;
    Graph(vector<Edge> &edges, int n);   // Constructor
    void addEdge(Graph &graph, int u, int v);   // to add an edge to graph
    bool edgeExists(Graph &graph, int u, int v); //check if edge exists
    bool hasCycle(Graph &graph, vector<int> &path);    // returns true if there is a cycle in this graph
    void displayGraph(Graph &graph);
    void EdmondsAlgorithm(int n);
    int findACycle(int vertex, unordered_map<int, Edge*>& vertexToMinEdge, unordered_set<int>& toRoot, unordered_set<int>& currentPath, unordered_set<Edge*>& cycleEdges, unordered_set<int>& cycleNodes);
    void DFS(int n, unordered_set<int>& seen);
    void MST(vector<vector<Pair>> adjList);
    void countEdges(Graph const &graph);
    void clearGraph(vector<vector<Pair>> adjList, int n);
	void resetGraph(vector<vector<Pair>> adjList, vector<Edge> edges, int n);
    bool isSC(Graph &graph); //returns true if there are strong connection between graph
    void getReverse(Graph &graph); //for bool isSC
	
	
    ~Graph() { }
};

#endif
