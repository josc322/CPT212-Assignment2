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

int main()
{
	// graph edges array.
    vector<Edge> edges = {
        // (x, y, w) -> edge from x to y with weight w
        {0,4,10216.47},{1,2,488.05},{2,3,1526.20},{3,4,3770.79},{0,1,7016.11}
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
	
	cout << "\t=============================================\n";
	cout << "\t|        Country       |         City        |\n ";
	cout << "\t=============================================\n";
	cout << "\t|     United States    |       Nashville     |\n";
	cout << "\t|        France        |         Paris       |\n";
	cout << "\t|        Zurich        |      Switzerland    |\n";
	cout << "\t|        Porto         |        Portugal     |\n";
	cout << "\t|        Cairo         |         Egypt       |\n"; 
	cout << "\t=============================================\n";
	
	cout<<"Directed weighted graph between the five cities using adjacency list:\n";
	
    g.displayGraph(g);
    
}
