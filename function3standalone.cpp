#include<iostream>
#include<set>
#include<list>
#include<algorithm>
#include<string>
using namespace std;

typedef struct nodes { // declare vertex
   int dest;
   int cost;
}node;

class Graph { // class graph
   int n;
   list<node> *adjList;
   private: // private class members
      void showList(int src, list<node> lt) { // function to show all vertexes
         list<node> :: iterator i;
         node tempNode;

         for(i = lt.begin(); i != lt.end(); i++) {
            tempNode = *i;
            cout << "(" << src << ")---("<<tempNode.dest << "|"<<tempNode.cost<<") ";
         }
         cout << endl;
      }
   public: // public class members
      Graph() {
         n = 0;
      }

      Graph(int nodeCount) {
         n = nodeCount;
         adjList = new list<node>[n];
      }

      void addEdge(int source, int dest, int cost) { // function to add edges from main
         node newNode;
         newNode.dest = dest;
         newNode.cost = cost;
         adjList[source].push_back(newNode);
      }

      void displayEdges() { // function to shows edges from main
         for(int i = 0; i<n; i++) {
            list<node> tempList = adjList[i];
            showList(i, tempList);
         }
      }
//      void edgeExists(int source, int dest, int cost){
//      	
//	  }

      friend void dijkstra(Graph g, int *dist, int *prev, int start); // friend function dijkstra 
};

void dijkstra(Graph g, int *dist, int *prev, int start) { //dijkstra function
   int n = g.n;

   for(int u = 0; u<n; u++) {
      dist[u] = 999999999;   //set as infinity(means no path)
      prev[u] = -1;    //undefined previous (doesnt have a previous vertex visited)
   }

   dist[start] = 0;   //default start = 0
   set<int> S;       //empty set S
   list<int> Q;

   for(int u = 0; u<n; u++) {
      Q.push_back(u);    //add each vertex into queue
   }

   while(!Q.empty()) {
      list<int> :: iterator i;
      i = min_element(Q.begin(), Q.end());
      int u = *i; //the minimum element from queue
      Q.remove(u);
      S.insert(u); //add u in the set
      list<node> :: iterator it;

      for(it = g.adjList[u].begin(); it != g.adjList[u].end();it++) {
         if((dist[u]+(it->cost)) < dist[it->dest]) { //relax (u,v)
            dist[it->dest] = (dist[u]+(it->cost));
            prev[it->dest] = u;
         }
      }
   }
}

int main() 
{
	int choice;
	cout<<"Shortest Path Dijkstra "<<endl;
	
	do{
		int u,v;
		int n = 5;
		Graph g(n);
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
		
		g.addEdge(0, 4, 10216.47); //Nashville to Cairo
		g.addEdge(1, 2, 488.05);  //Paris to Zurich
		g.addEdge(2, 3, 1526.20); //Zurich to Porto
		g.addEdge(3, 4, 3770.79); //Cairo to Porto
		g.addEdge(0, 1, 7016.11); //Nashville to Paris
		
		dijkstra(g, dist, prev, start);
		
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

	cout<<"\n\n1 - Continue"<<endl;
	cout<<"0 - Exit"<<endl;
	cout<<"Do you wish to continue? : ";
	cin>>choice;       	
	
	}while(choice!=0);
  	
}
  

