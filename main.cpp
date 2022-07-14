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
using namespace std;

void graphDisplay(Graph g);
Graph detectCycle(Graph g);
Graph addEdges(Graph g);

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
     cout << "2. Check Connectivity"<<endl;
     cout << "3. Detect Cycle"<<endl;
     cout << "4. Check Strongest Path"<<endl;
     cout << "5. Check Minimum Spanning Tree"<<endl;
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
			case 3:
				g = detectCycle(g);
				break;
			case 5:
				g.MST(g.adjList);
				break;
			case 6:
				g.countEdges(g);
				break;
			case 8:
				g = addEdges(g);
				break
				//add more cases in between
			case 10:
				g.resetGraph(g.adjList, edges, vertices);
				cout << "Graph have been reset to default graph.";
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
