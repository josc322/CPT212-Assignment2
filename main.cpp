/*******************************************************************************
/* Assignment 2 CPT212
/* What the program do: Apply basic graph functions to a directed weighted graph.
/* Programmer Name: HANA SHAH BINTI FAIZAL SHAH
/* Programmer Matric #: 153583
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

int main()
{
	// graph edges array.
    vector<Edge> edges = {
        // (x, y, w) -> edge from x to y with weight w
        {1,5,10216.47},{2,3,488.05},{3,4,1526.20},{4,5,3770.79},{1,2,7016.11}
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
     cout << "6. Add Edge Count"<<endl;
     cout << "7. Transpose Graph"<<endl;
     cout << "8. Add Edge"<<endl;
     cout << "9. Remove Edge"<<endl;
     cout << "10. Exit Program"<<endl;
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
				//add more cases in between
			case 10:
				break;
		default: //if choice not 1-10
				cout << "Invalid Choice" << endl;
				system("pause");
		}
	}while (choice != 10);
	
	cout << "\nEnd of program";
  
    return 0;
	
}

//Display Graph
void graphDisplay(Graph g){
	
	cout<<"Directed weighted graph between five cities using Adjacency List\n";
	
    g.displayGraph(g);
    
}