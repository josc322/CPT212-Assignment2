/*******************************************************************************
/* Assignment 2 CPT212
/* What the program do: Apply basic graph functions to a directed weighted graph.
/* Programmer Name #1: NURUL IFFAH BINTI MOHD ZUKHI
/* Programmer Matric #1: 151183
/* Programmer Name #2: HANA SHAH BINTI FAIZAL SHAH
/* Programmer Matric #2: 153583
/* Programmer Name #3: SYED MUHAMMAD HAIKAL BIN SYED HUSNI
/* Programmer Matric #3: 153086
/* Programmer Name #4: JAZREEL OOI SUE CHING
/* Programmer Matric #4: 150740
/******************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>
#include <cstdlib>
#include "Graph.h"
#include "Graph2.h"
using namespace std;

void graphDisplay(Graph g);
Graph detectCycle(Graph g);
Graph addEdges(Graph g);
Graph removeEdges(Graph g);
Graph strongConnect(Graph g);
void shortestPath();
void reverseGraph();
void minimumST(Graph g);
Graph resetGraph(Graph g, vector<Edge> edges, int n);

const int vertices = 5;

int main()
{
	// graph edges array.
    vector<Edge> edges = {
        // (x, y, w) -> edge from x to y with weight w
        {0,4,10216},{1,2,488},{2,3,1526},{3,4,3771},{0,1,7016}
    };
    int vertices = 5;
    //Create graph
    Graph g(edges, vertices);
    
     cout << "Please choose the functions you want to do: "<<endl;
     cout << "--------------------------------------------"<<endl;
     cout << "1. Display Graph"<<endl;
     cout << "2. Check Strong Connectivity"<<endl;
     cout << "3. Detect Cycle"<<endl;
     cout << "4. Find Shortest Path"<<endl;
     cout << "5. Generate Minimum Spanning Tree"<<endl;
     cout << "6. Display Number of Edges"<<endl;
     cout << "7. Reverse Graph"<<endl;
     cout << "8. Add Edge"<<endl;
     cout << "9. Remove Edge"<<endl;
     cout << "10. Reset Graph" << endl;
     cout << "11. Exit Program"<<endl;
     cout << "--------------------------------------------"<<endl;
     
    int choice=0;
    
    //do-while loop until user choose to exit
	do{
		cout << "Enter function number: ";
		cin >> choice; 	//ask for menu choice
		cout << endl;
		
		switch (choice) //switch case for choice
		{
			case 1: 
				graphDisplay(g);
				break;
			case 2:
				strongConnect(g);
				break;
			case 3:
				g = detectCycle(g);
				break;
			case 4:
				shortestPath();
				break;
			case 5:
				minimumST(g);
				break;
			case 6:
				g.countEdges(g);
				break;
			case 7:
				reverseGraph();
				break;
			case 8:
				g = addEdges(g);
				break;
			case 9:
				g = removeEdges(g);
				break;
			case 10:
				g = resetGraph(g, edges, vertices);
				graphDisplay(g);
				break;
			case 11:
				break;
		default: //if choice not 1-10
				cout << "Invalid Choice" << endl;
				system("pause");
		}
	}while (choice != 11);
	
	cout << "\nEnd of program";
	
	g.~Graph(); //Destructor
  
    return 0;
	
}

//Display Graph
void graphDisplay(Graph g){
	cout << endl;
	cout << "\t=============================================\n";
	cout << "\t|        Country       |         City        |\n ";
	cout << "\t=============================================\n";
	cout << "\t|     United States    |       Nashville     |\n";
	cout << "\t|        France        |         Paris       |\n";
	cout << "\t|      Switzerland     |        Zurich       |\n";
	cout << "\t|       Portugal       |         Porto       |\n";
	cout << "\t|        Egypt         |         Cairo       |\n"; 
	cout << "\t=============================================\n";
	
	cout<<"Directed weighted graph between the five cities using adjacency list:\n";
	
    g.displayGraph(g);
    
}

Graph detectCycle(Graph g){
	//The source vertex and destination vertex
	int u,v;
	
	//The path of the cycle
	vector<int> cyclePath;
	//The vertices of the graph represented by the five cities
	string location[vertices] = {"Nashville","Paris","Zurich","Porto","Cairo"};
	
	//Detect cycle, the graph and path of the cycle is passed to the function
	if(g.hasCycle(g,cyclePath)){ //If graph contains cycle
        cout << "Graph contains cycle\n";
        //Displays the path of the cycle
        cout << "Cycle detected: ";
        for (int i = cyclePath.size()-1; i >= 0; --i) {
            if (i==0){ //last node in the cycle
            	cout << location[cyclePath[i]];
			}
			else
			 cout << location[cyclePath[i]] << "->";
        	}
        cout<<endl<<endl;
    }
    else{ //If path does not contain cycle
        cout << "Graph doesn't contain cycle\n";
		//Generates random edge until a cycle is detected	
        cout << "Generating random edge..."<<endl;
        a:
        u = rand()%5; //Generate random number from 0 to 4 for the source and destination vertex
        v = rand()%5;
        //Check if edge exists
		if(g.edgeExists(g, u, v)){ //If edge exists, generate random numbers for the source and destination vertex again
			cout << "This edge already exists! Generating random edge...\n";
			goto a;
		}
		else{ //If edge does not exists, the edge is added to the graph
			g.addEdge(g,u,v);
        	detectCycle(g); //Function call to detect cycle
		}
	}
	
	return g; //Return the updated graph
}

Graph addEdges(Graph g){
	//The source vertex and destination vertex
	int u, v;
	
	cout << "\t=============================================\n";
	cout << "\t|      Vertex No       |         City        |\n ";
	cout << "\t=============================================\n";
	cout << "\t|          0           |       Nashville     |\n";
	cout << "\t|          1           |         Paris       |\n";
	cout << "\t|          2           |        Zurich       |\n";
	cout << "\t|          3           |         Porto       |\n";
	cout << "\t|          4           |         Cairo       |\n"; 
	cout << "\t=============================================\n";
	
	//User input
	a:
	cout << "Enter number of source vertex: ";
	cin >> u;
	//User input validation
	while (u < 0 || u > 4)
	{
		// An error message will appear if user enters incorrect input
		cout << "\nERROR! Please enter the correct vertex number according to the table above: ";
		cin >> u;
	}
	
	//User input
	cout << "Enter number of destination vertex: ";
	cin >> v;
	//User input validation
	while (v < 0 || v > 4)
	{
		// An error message will appear if user enters incorrect input
		cout << "\nERROR! Please enter the correct vertex number according to the table above: ";
		cin >> v;
	}
	
	//Check if edge exists
	if(g.edgeExists(g, u, v)){ //If edge exists, error message will appear and user will be asked to enter a different input
		cout << "This edge already exists! Please enter a different input.\n";
		goto a;
	}
	else{ //If edge does not exist, the new edge will be added to the graph.
		g.addEdge(g, u, v);
		cout<< "The new edge has been added to the graph.\n\n";
		}
	return g; //Return the updated graph.
}

void shortestPath(){
		cout<<"Shortest Path Dijkstra "<<endl;
		
		int u,v;
		int n = 5;
		Graph2 g2(n);
		int dist[n], prev[n];
		
		string City[n] = {"Nashville", "Paris", "Zurich", "Porto", "Cairo"};
		
		int pick1;
		int pick2;
		
		int o=0;
		int m=0;
		
		cout<<endl;
		cout << "Pick starting city" << endl;
		while (o<n){
		cout << o <<") " << City[o] << endl;
		o++;
		}
		cout << "Pick a number of the starting city : ";
		cin >> pick1;
		
		while (o<m){
		cout << m <<") " << City[m] << endl;
		m++;
		}
		cout << "Pick a number of the ending city : ";
		cin >> pick2;
		
		int start = pick1;
		
		g2.addEdge(0, 4, 10216.47); //Nashville to Cairo
		g2.addEdge(1, 2, 488.05);  //Paris to Zurich
		g2.addEdge(2, 3, 1526.20); //Zurich to Porto
		g2.addEdge(3, 4, 3770.79); //Cairo to Porto
		g2.addEdge(0, 1, 7016.11); //Nashville to Paris
		
		dijkstra(g2, dist, prev, start);
		
		cout<<endl;
		for(int i = 0; i<n; i++)
		  if(i != start)
		     cout<<start<<" to "<<i<<", Distance: "<<dist[i]<<"KM"<<" Previous: "<<prev[i]<<" cities "<<endl;
		
		
		for(int i = 0; i<n; i++)
		  if(i != start)
		  		if(i == pick2 && prev[i] != -1)
		  			{
		  			cout<<endl;
		     		cout<<City[start]<<" to "<<City[i]<<", Distance: "<<dist[i]<<"KM "<<endl;
		     		 int k=prev[i];
		     		cout << "Previous city  : "<<City[k]<<endl;
		     		//apa2=true
		  			}
		     	else if(i == pick2 && prev[i] == -1){
		     		
				 	cout<<endl;
		     		cout << "There is no path"<<endl<<endl;
		     		//apa2 = false while loop satu main
		     		//tambah edge kat sini
		     		cout<<"Generating random edge..."<<endl;
		     		
//		     		if(g.edgeExists(pick1,u, v)){
//		     			cout<<"This edge already exists!";
//					 }
		     	}  
}

Graph removeEdges(Graph g){
	//The source vertex and destination vertex
	int u, v;
	
	cout << "\t=============================================\n";
	cout << "\t|      Vertex No       |         City        |\n ";
	cout << "\t=============================================\n";
	cout << "\t|          0           |       Nashville     |\n";
	cout << "\t|          1           |         Paris       |\n";
	cout << "\t|          2           |        Zurich       |\n";
	cout << "\t|          3           |         Porto       |\n";
	cout << "\t|          4           |         Cairo       |\n"; 
	cout << "\t=============================================\n";
	
	//User input
	a:
	cout << "Enter number of source vertex: ";
	cin >> u;
	//User input validation
	while (u < 0 || u > 4)
	{
		// An error message will appear if user enters incorrect input
		cout << "\nERROR! Please enter the correct vertex number according to the table above: ";
		cin >> u;
	}
	
	//User input
	cout << "Enter number of destination vertex: ";
	cin >> v;
	//User input validation
	while (v < 0 || v > 4)
	{
		// An error message will appear if user enters incorrect input
		cout << "\nERROR! Please enter the correct vertex number according to the table above: ";
		cin >> v;
	}
	
	//Check if edge exists
	if(g.edgeExists(g, u, v)){ //If edge exists, the edge will be removed
		g.removeEdge(g , u ,v);
		cout<< "The edge has been removed from the graph.\n\n";
	}
	else{ //If edge exists, error message will appear and user will be asked to enter a different input
		cout<< "The edge does not exist! Please enter a different input.\n";
		goto a;
		}
	return g; //Return the updated graph.
}

Graph strongConnect(Graph g)
{
	//The source vertex and destination vertex
	int u,v;
	
	if(g.isSC(g))
		cout << "Graph is strongly connected." << endl;
	else
	{
		cout << "Graph is not strongly connected." << endl;
		//Generates random edges until graph is strongly connected
        cout << "Generating random edge..."<<endl;
        a:
        u = rand()%5; //Generate random number from 0 to 4 for the source and destination vertex
        v = rand()%5;
        //Check if edge exists
		if(g.edgeExists(g, u, v)){ //If edge exists, generate random numbers for the source and destination vertex again
			cout << "This edge already exists! Generating random edge..." << endl;
			goto a;
		}
		else{ //If edge does not exists, the edge is added to the graph
			g.addEdge(g,u,v);
        	strongConnect(g); //Function call to check connectivity
		}
	}
	return g;
}

void reverseGraph()
{
	// traverse the adjacency list of given graph
    vector<Edge> revedges = {
        // (y, x, w) -> edge from y to x with weight w
        {4,0,10216},{2,1,488},{3,2,1526},{4,3,3771},{1,0,7016}
    };
    
   int revertices = 5;
   Graph g(revedges, revertices);
   g.displayGraph(g);
}

// Function of Minimum Spanning Tree
void minimumST(Graph g){
	// Add edges to the graph to make it become undirected graph
	g.addEdge(g, 1, 0);
	g.addEdge(g, 2, 1);
	g.addEdge(g, 3, 2);
	g.addEdge(g, 4, 3);
	g.addEdge(g, 4, 0);
	cout << "This is an undirected graph:\n";
	
	// Display the current graph
	graphDisplay(g);
	
	// User's input for the number of edges
    int n;
    
    // Display message
    cout << "Enter the number of edges to generate a Minimum Spanning Tree: \n";
    cin >> n;
    if(n != 4){
    	cout << "You cannot find a MST with this number entered!\n\n";
    	cout << "Generating random edges right now...\n\n";
    	
    	// Start vertex and end vertex
    	int u, v;
    	
    	//Generate random number from 0 to 4 for the source and destination vertex
    	a:
    	u = rand()%5; 
        v = rand()%5;
        
        if(g.edgeExists(g, u, v)){ //If edge exists, generate random numbers for the source and destination vertex again
			cout << "This edge already exists!\n\nGenerating random edge..." << endl;
			goto a;
		}
		else{ //If edge does not exists, the edge is added to the graph
			g.addEdge(g,u,v);
			
			// Call the PrimsAlogrithm function
			g.PrimsAlgorithm(vertices, g.adjList);
		}
	} else {
		// Call the PrimsAlgorithm function
		g.PrimsAlgorithm(vertices, g.adjList);
	}	
}

// Reset the graph back to default mode
Graph resetGraph(Graph g, vector<Edge> edges, int n){
	// Call clearGraph function
	g.clearGraph(g);
	
	// Initialize the graph
	Graph graph(edges, n);
	cout << "Graph has been reset. Displaying graph..\n\n";
	
	return graph;
}
