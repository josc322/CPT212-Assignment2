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



