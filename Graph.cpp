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
        }
}

void Graph::displayGraph(Graph &graph)
{
	int V = 5; //number of vertices
	
	//The vertices of the graph represented by the five cities
	string location[V] = {"Nashville","Paris","Zurich","Porto","Cairo"};
        
    for (int i = 0; i < V; i++)
    {   
		// Function to print all neighboring vertices of a given vertex
	    for (Pair v: graph.adjList[i]) {
	        cout << location[i]<<" -> " << location[(v.first)] << ",(" << v.second << "KM) ";
	    }
	    cout << endl;
	}
	cout<<endl;
}

void Graph::countEdges(Graph const &graph){
	int result = 0;
	int n = 5;

	//Count the number of edges
	for(int i = 0; i < n; i++){
		for(auto it: graph.adjList[i]){
			result++;
		}
	}
	
	cout << "Number of edges: " << result << endl;
}

bool Graph::hasCycleUtil(Graph &graph, int a, bool visited[], bool *recStack, vector<int> &path)
{	
    if(visited[a] == false) //If current node is not visited
    {
        // Mark the current node as visited and part of recursion stack
        visited[a] = true;
        recStack[a] = true;
  
        // Recur for all the vertices adjacent to this vertex
   			for (Pair v: graph.adjList[a]) {
   				//If the adjacent node is not visited, a recursive call is made
   				if ( !visited[(v.first)] && hasCycleUtil(graph, (v.first), visited, recStack, path) ){
   					path.push_back(v.first); //the node that appears in the cycle is added into the vector
                	return true;
                }
                //if the adjacent node is already visited, the node is checked in the recursion stack
            	else if (recStack[v.first]){
            		path.push_back(v.first); //the node that appears in the cycle is added into the vector
                	return true;
                }
			   }
        
    }
    recStack[a] = false;  //Remove the vertex from recursion stack
    return false;
}

bool Graph::hasCycle(Graph &graph, vector<int> &path)
{
	//Depth-First-Search is used to find cycles in the graph
	int V = 5; //Number of vertices
	
    // Mark all the vertices as not visited and not part of recursion stack
    bool *visited = new bool[V];
    bool *recStack = new bool[V];
    

    //Initially mark all nodes unvisited and not part of the recursion stack
    for(int i = 0; i < V; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }
    
    // Call the recursive helper function to detect cycle in different DFS trees
    for(int i = 0; i < V; i++)
    	//Send the starting node and the arrays
        if ( !visited[i] && hasCycleUtil(graph,i, visited, recStack, path)){
        	return true; //Cycle detected
		}

    return false; //Cycle not detected
}  


void Graph::addEdge(Graph &graph, int u, int v)
{
	//Declare variable for weight
	int w;
	
	//Distances between two cities
	if((u==0 && v==1) || (u==1 && v==0)) //Nashville to Paris/Paris to Nashville
		w = 7016;
	else if((u==0 && v==2) || (u==2 && v==0)) //Nashville to Zurich/Zurich to Nashville
		w = 7500;
	else if((u==0 && v==3) || (u==3 && v==0)) //Nashville to Porto/Porto to Nashville
		w = 8244;
	else if((u==0 && v==4) || (u==4 && v==0)) //Nashville to Cairo/Cairo to Nashville
		w = 10216;
	else if((u==1 && v==2) || (u==2 && v==1)) //Paris to Zurich/Zurich to Paris
		w = 488;
	else if((u==1 && v==3) || (u==3 && v==1)) //Paris to Porto/Porto to Paris
		w = 10254;
	else if((u==1 && v==4) || (u==4 && v==1)) //Paris to Cairo/Cairo to Paris
		w = 3210;
	else if((u==2 && v==3) || (u==3 && v==2)) //Zurich to Porto/Porto to Zurich
		w = 1526;
	else if((u==2 && v==4) || (u==4 && v==2)) //Zurich to Cairo/Cairo to Zurich
		w = 2736;
	else if((u==3 && v==4) || (u==4 && v==3)) //Porto to Cairo/Cairo to Porto
		w = 3771;
	else // City to itself 
		w = 0;
	
	//Add edges to the graph
    graph.adjList[u].push_back(make_pair(v, w));
}

bool Graph::edgeExists(Graph &graph, int u, int v){

    // if source and destination vertex are the same
    if (u == v)
      return true;
 
    //Check the adjacent nodes of the vertex
    for (Pair p: graph.adjList[u])
    {
        // If this adjacent node is the destination node, then
        // return true
        if (p.first == v)
            return true;
        else
           	return false;
        }
    
    return false;
}

void Graph::clearGraph(vector<vector<Pair>> adjList, int n)
{
	for(int i = 0; i < n; i++){
		for(auto it : adjList[i]){
			adjList[i].clear();
		}
	}
}

void Graph::resetGraph(vector<vector<Pair>> adjList, vector<Edge> edges, int n){
	clearGraph(adjList, n);
	Graph(edges, n);
}

void Graph::DFS(int n, unordered_set<int>& seen) {
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

void Graph::EdmondsAlgorithm(int n) {
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
    EdmondsAlgorithm(n);
    
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
}

void Graph::MST(vector<vector<Pair>> adjList){
	int noVertices, noEdges;
	int start, destination;
	
    cout << "Enter the number of vertices: ";
    cin >> noVertices;
    noEdges = noVertices-1;
	cout << "Enter the starting vertex: ";
	cin >> start;
	cout << "Enter the destination vertex: ";
	cin >> destination;
	
	// Initialize empty nodes
    nodes.resize(noVertices);

    for (int i = 0; i <= noVertices; i++) {
        nodes[i] = new Node;
    }

    // Parse edge information. Do not add edge (u,v) with weight w if:
    // 1. v = 0 since we assume 0 is our root node
    // 2. u == v since this will never be in a minimum directed spanning tree
    // 3. There is already an edge (u,v) with weight w' and w >= w'
    for (int i = start; i <= destination - start; i++) {
        int u, v, w;
        u = i;
        cout << u << endl;
        for(auto it : adjList[i]){
        	v = it.first;
        	cout << v << endl;
        	w = it.second;
        	cout << w << endl;
		}
//        cout << "Enter the parent node: ";
//        cin >> u;
//        cout << "Enter the child node: ";
//        cin >> v;
//        cout << "Enter the weight: ";
//        cin >> w;

        if (v == 0 
            || u == v
            || (nodes[v]->edgesComingIn.find(u) != nodes[v]->edgesComingIn.end() 
                && w >= nodes[v]->edgesComingIn[u]->weight)
        ) {
            continue;
        }

        Edge* edge = new Edge(u, v, w);
        nodes[u]->edgesGoingOut[v] = edge;
        nodes[v]->edgesComingIn[u] = edge;
    }
    
    // Use DFS to determine if there is a path from the root vertex to all other vertices.
    // If there is not, there is no spanning directed tree and thus no minimum directed
    // spanning tree
    unordered_set<int> seen;
    DFS(0, seen);
    if (seen.size() < noVertices) {
        cout << "No solution!" << endl;
    }

    EdmondsAlgorithm(noVertices);

    // Every vertex in the MDST (except for the root) has one and only edge going into it.
    // Sum the weights of all the edges in the MDST by traversing the singular edge going
    // into each vertex
    int sum = 0;
    cout << "Minimum spanning tree: " << endl;
    for (int i = 1; i < noVertices; i++) {
        Edge* edge = nodes[i]->edgeInMDST;
        sum += edge->weight;
        cout << edge->src << "->" << edge->dest << " " << edge->weight << endl;
    }
    cout << "Minimum spanning tree total cost: " << sum << endl;
}

// A recursive function to print DFS starting from v
void Graph::DFSUtil(Graph &graph, int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;
 
    // Recur for all the vertices adjacent to this vertex
    vector<pair<int, int>>::iterator i;
    for (i = adjList[v].begin(); i != adjList[v].end(); ++i)
    {
    if (!visited[(*i).first])
	{DFSUtil(graph, (*i).first, visited);}
    }
}

void Graph::getReverse(Graph &graph)
{
	int V=5;
	
	for(int v=0; v<V; v++){
		for(Pair p: graph.adjList[v]){
			graph.adjList[p.first].push_back(make_pair(v,p.second));
		}
	}
	
}

bool Graph::isSC(Graph &graph)
{
    // St1p 1: Mark all the vertices as not visited
    // (For first DFS)
    int V = 5;
    bool *visited = new bool [V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
 
    // Step 2: Do DFS traversal starting from first vertex.
    DFSUtil(graph, 0, visited);
 
     // If DFS traversal doesn’t visit all vertices,
     // then return false.
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
             return false;
 
   // Step 3: Create a reversed graph
    Graph:getReverse(graph);
    
 
    // Step 4: Mark all the vertices as not visited
    // (For second DFS)
    for(int i = 0; i < V; i++)
        visited[i] = false;
 
    // Step 5: Do DFS for reversed graph starting from
    // first vertex. Starting Vertex must be same starting
    // point of first DFS
    getReverse:DFSUtil(graph, 0, visited);
 
    // If all vertices are not visited in second DFS, then
    // return false
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
             return false;
 
    return true;
}



