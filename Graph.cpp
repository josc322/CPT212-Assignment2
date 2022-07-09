#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>
#include "Graph.h"
using namespace std;

Graph::Graph(vector<Edge> const &edges, int n)
{
        // resize the vector to hold `n` elements of type vector<Edge>
        adjList.resize(n);
 
        // add edges to the directed graph
        for (auto &edge: edges)
        {
            int src = edge.src;
            int dest = edge.dest;
            float weight = edge.weight;
 
            // insert at the end
            adjList[src].push_back(make_pair(dest, weight));
 
            // uncomment the following code for undirected graph
            // adjList[dest].push_back(make_pair(src, weight));
        }
}

void Graph::displayGraph(Graph const &graph)
{
	int n = 5;
	string location[n] = {"Nashville","Paris","Zurich","Porto","Cairo"};
        
    for (int i = 0; i < n; i++)
    {   
		// Function to print all neighboring vertices of a given vertex
	    for (Pair v: graph.adjList[i]) {
	        cout << location[i-1]<<" -> " << location[(v.first)-1] << ",(" << v.second << "KM) ";
	    }
	    cout << endl;
	}
	cout<<endl;
}

/*  
void Graph::addEdge(vector <pair<int, int> > adjacencyList[], int u,
                                     int v, float wt)
{
    adjacencyList[u].push_back(make_pair(v, wt));
    adjacencyList[v].push_back(make_pair(u, wt));
}*/
