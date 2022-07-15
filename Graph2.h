#ifndef GRAPH2_H
#define GRAPH2_H
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

class Graph2 { // class graph
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
      Graph2() {
         n = 0;
      }

      Graph2(int nodeCount) {
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

      friend void dijkstra(Graph2 g, int *dist, int *prev, int start); // friend function dijkstra 
};

void dijkstra(Graph2 g, int *dist, int *prev, int start) { //dijkstra function
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

#endif