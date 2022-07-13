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
            int weight = edge.weight;
 
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
	        cout << location[i]<<" -> " << location[(v.first)] << ",(" << v.second << "KM) ";
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

/*void Graph::DFS(int n, unordered_set<int>& seen) {
    seen.insert(n);
    for (auto &edge : nodes[n]->edgesGoingOut) {
        if (seen.find(edge.first) == seen.end()) {
            DFS(edge.first, seen);
        }
    }
}

int Graph::findACycle(int vertex, unordered_map<int, Edge*>& vertexToMinEdge, unordered_set<int>& toRoot, unordered_set<int>& currentPath, unordered_set<Edge*>& cycleEdges, unordered_set<int>& cycleNodes) {
    currentPath.insert(vertex);
    
    Edge* edge = vertexToMinEdge[vertex];
    int parentVertex = edge->src;
    if (parentVertex == 0) { 
        // Parent vertex is root vertex
        return false;
    } 

    if (toRoot.find(parentVertex) != toRoot.end()) { 
        // Parent vertex leads to root
        toRoot.insert(vertex);

        return false;
    } else if (currentPath.find(parentVertex) == currentPath.end()) { 
        // Haven't seen parent vertex before so recurse
        int foundCycle = findACycle(parentVertex, vertexToMinEdge, toRoot, currentPath, cycleEdges, cycleNodes);
        if (foundCycle && foundCycle != parentVertex) { 
            // Second check is to see if vertex does not belong in foundCycle
            cycleEdges.insert(edge);
            cycleNodes.insert(vertex);

            return foundCycle;
        } else {
            toRoot.insert(vertex);

            return false;
        }
    } else {
        // Have seen parent vertex in current path before so this is a cycle
        cycleEdges.insert(edge);
        cycleNodes.insert(vertex);

        return parentVertex;
    }
}

void Graph::MDST(int n) {
    // Find the edge of minimum weight going into every vertex other than the root
    // with ties broken arbitrarily
    unordered_map<int, Edge*> vertexToMinEdge;
    for (int i = 1; i < n; i++) {
        if (nodes[i]->edgesComingIn.size() == 0) {
            continue;
        }

        int minCost = 2147483647;
        Edge* minEdge;
        for (auto &edge : nodes[i]->edgesComingIn) {
            if (edge.second->weight < minCost) {
                minEdge = edge.second;
                minCost = edge.second->weight;
            }
        }

        vertexToMinEdge[i] = minEdge;
    }

    // Determine if there is a cycle in the set of minimum weight edges for each vertex by
    // iterating over every vertex (that has a min edge in the current version of the graph) and 
    // determine whether it leads to a cycle
    int cycleFound = 0;
    // toRoot: Memoized set of vertices that lead to root node (for performance)
    unordered_set<int> toRoot;
    // currentPath: Set of vertices in current path, if we encounter one of these vertices
    // again we have found a cycle
    unordered_set<int> currentPath;
    // cycleNodes and cycleEdges: Variables to store results from function
    unordered_set<Edge*> cycleEdges;
    unordered_set<int> cycleNodes;
    for (auto &vertex : vertexToMinEdge) {
        currentPath.clear();
        cycleFound = findACycle(vertex.first, vertexToMinEdge, toRoot, currentPath, cycleEdges, cycleNodes);

        if (cycleFound) {
            break;
        }
    }

    // If there is no cycle then all the edges in vertexToMinEdge belong in the MDST
    if (!cycleFound) {
        for (auto &edge : vertexToMinEdge) {
            nodes[edge.first]->edgeInMDST = edge.second;
        }

        return;
    }

    // Create new concatenated node
    n++;
    nodes.push_back(new Node); 

    // Update the graph to have all edges with a vertex in the cycle to point to new concatenated node v_C.
    // Maintain information on what we are changing in order to reverse the changes
    unordered_map<Edge*, Edge*> changedEdges;
    unordered_set<Edge*> edgesToErase;
    for (auto &vertex : cycleNodes) {
        for (auto &edge : nodes[vertex]->edgesComingIn) {
            // Check to see if both u and v are in cycle
            if (cycleNodes.find(edge.second->src) == cycleNodes.end()) {
                // Determine updated cost of edge based on Edmonds' algorithm
                int updatedWeight = edge.second->weight - vertexToMinEdge[vertex]->weight;
                // Check to see if there is already an edge coming into the new vertex from
                // this vertex. If there is, update the edge if updatedWeight has a smaller weight
                // and if not, discard this edge
                if (nodes[n - 1]->edgesComingIn.find(edge.second->src) != nodes[n - 1]->edgesComingIn.end()) {
                    if (updatedWeight >= nodes[n - 1]->edgesComingIn[edge.second->src]->weight) {
                        edgesToErase.insert(edge.second);
                        continue;
                    } else {
                        edgesToErase.insert(changedEdges[nodes[n - 1]->edgesComingIn[edge.second->weight]]);
                    }
                }
                
                // Store old edge and then update edge
                changedEdges[edge.second] = new Edge(edge.second->weight, edge.second->dest, edge.second->weight);
                nodes[edge.second->src]->edgesGoingOut.erase(edge.second->weight);

                edge.second->dest = n - 1;
                edge.second->weight = updatedWeight;
                nodes[n - 1]->edgesComingIn[edge.second->src] = edge.second;
                nodes[edge.second->src]->edgesGoingOut[n - 1] = edge.second;
            } else {
                // If both u and v are in cycle, remove edge from graph completely
                edgesToErase.insert(edge.second);
            }
        }
        nodes[vertex]->edgesComingIn.clear();
        for (auto &edge : nodes[vertex]->edgesGoingOut) {
            // Check to see if both u and v are in cycle
            if (cycleNodes.find(edge.second->dest) == cycleNodes.end()) {
                // Check to see if there is already an edge coming into the new vertex from
                // this vertex. If there is, update the edge if it has a smaller weight
                // and if not, discard this edge
                if (nodes[n - 1]->edgesGoingOut.find(edge.second->dest) != nodes[n - 1]->edgesGoingOut.end()) {
                    if (edge.second->weight >= nodes[n - 1]->edgesGoingOut[edge.second->dest]->weight) {
                        edgesToErase.insert(edge.second);
                        continue;
                    } else {
                        edgesToErase.insert(changedEdges[nodes[n - 1]->edgesGoingOut[edge.second->dest]]);
                    }
                }
                // Store old edge and then update edge
                changedEdges[edge.second] = new Edge(edge.second->src, edge.second->dest, edge.second->weight);
                nodes[edge.second->dest]->edgesComingIn.erase(edge.second->src);
                
                edge.second->src = n - 1;
                nodes[n - 1]->edgesGoingOut[edge.second->dest] = edge.second;
                nodes[edge.second->dest]->edgesComingIn[n - 1] = edge.second;
            } else {
                // If both u and v are in cycle, remove edge from graph completely
                edgesToErase.insert(edge.second);
            }
        }
        nodes[vertex]->edgesGoingOut.clear();
    }

    for (auto &edge : edgesToErase) {
        nodes[edge->src]->edgesGoingOut.erase(edge->dest);
        nodes[edge->dest]->edgesComingIn.erase(edge->src);
    }

    // Recurse on new updated graph with node v_C
    MDST(n);
    
    // Let (u, v_C) be the unique incoming edge to v_C in A'. 
    // This edge corresponds to an edge (u,v) in E with v in C. 
    // Remove the edge vertexToMinEdge(v) from C
    Edge* edgeGoingIntoConcatenatedNode = nodes[n - 1]->edgeInMDST;
    int node = changedEdges[edgeGoingIntoConcatenatedNode]->dest;
    cycleEdges.erase(vertexToMinEdge[node]);

    // Add the remaining edges in the cycle to MDST
    for (auto &edge : cycleEdges) {
        nodes[edge->dest]->edgeInMDST = edge;
    }

    // Insert the original edge going into concatenated node into MDST
    Edge* oldEdge = changedEdges[edgeGoingIntoConcatenatedNode];
    nodes[oldEdge->dest]->edgeInMDST = edgeGoingIntoConcatenatedNode;
    // Revert all changes to edges we made
    for (auto &edge: changedEdges) {
        edge.first->src = edge.second->src;
        edge.first->dest = edge.second->dest;
        edge.first->weight = edge.second->weight;

        nodes[edge.first->dest]->edgesComingIn[edge.first->src] = edge.first;
        nodes[edge.first->src]->edgesGoingOut[edge.first->dest] = edge.first;
    }

    n--;
}*/
