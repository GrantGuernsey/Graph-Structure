#include "Graph.h"
#include <iostream>
#include <list>
using namespace std;

/* GRAPH IS OF TYPE INT */

void test() {
  Graph x;

  x.addVertex(4); // Starting node
  x.addVertex(5);
  x.addVertex(1);
  x.addVertex(3);
  x.addVertex(2);

  x.addVertex(10); // Isolated node

  x.addEdge(4, 5, 0); // 1st path added to 4 (edges.push_back)
  x.addEdge(4, 1, 0); // 2nd path added to 4 (edges.push_back)

  x.addEdge(5, 3, 0); // 1st path added to 5 (edges.push_back)
  x.addEdge(5, 2, 0); // 2nd path added to 5 (edges.push_back)

  list<int> in = x.inEdges(5);
  list<int> out = x.outEdges(5);
  list<int> path = x.DFS(3);

  //Graph::print(in);
  //Graph::print(out);
  cout << "Depth First Search: " << endl;
  Graph::print(path);
	cout << "Breadth First Search: " << endl;
  x.BFS(3);
}

void eventLoop() {
  Graph g;
  cout << "How many vertices do you have on your graph? ";
  int numVert;
  cin >> numVert;
  for (int i = 1; i <= numVert; i++){
    g.addVertex(i);
  }
  cout << numVert << " vertices added to graph." << endl;

  int option;
  bool looper = true;
  while (looper) {
    cout << endl << "Select an option by entering a value 1-8: " << endl;
    cout << "1. Add an Edge to the Graph" << endl;
    cout << "2. Remove an Edge from the Graph" << endl;
    cout << "3. Find an Edge in the Graph" << endl;
    cout << "4. Find the out Edges of a Vertices" << endl;
    cout << "5. Find the in Edges of a Vertices" << endl;
    cout << "6. Depth First Search" << endl;
    cout << "7. Breadth First Search" << endl;
    cout << "8. To Quit" << endl;

    cin >> option;

    if (option == 1) {
      // Add an edge
      int edge1, edge2;
      cout << "What vertices would you like your edge to start from? ";
      cin >> edge1;
      cout << "What vertices would you like your edge to go to? ";
      cin >> edge2;

      g.addEdge(edge1, edge2, 0);
      
    } else if (option == 2) {
      //Remove an edge
      int edge1, edge2;
      cout << "What is the first vertices you would like to remove your edge from? ";
      cin >> edge1;
      cout << "What is the second vertices you would like to remove your edge from? ";
      cin >> edge2;

      g.removeEdge(edge1, edge2);
      cout << "Edge successfully removed.";
      
    } else if (option == 3) {
      // Check has edge
      int edge1, edge2;
      cout << "What vertices does your edge to start from? ";
      cin >> edge1;
      cout << "What vertices does your edge go to? ";
      cin >> edge2;

      bool result = g.hasEdge(edge1, edge2);
      if (result == true){
        cout << "Edge between " << edge1 << " and " << edge2 << " exists." << endl;
      }
      else{
        cout << "Edge between " << edge1 << " and " << edge2 << " does not exist." << endl;
      }
      
    } else if (option == 4) {
      // Find out edges
      int vert;
      cout << "What vertices would you like to check the out edges of? ";
      cin >> vert;
      list<int> out = g.outEdges(vert);
      Graph::print(out);
      
    } else if (option == 5) {
      // Find in edges
      int vert;
      cout << "What vertices would you like to check the in edges of? ";
      cin >> vert;
      list<int> in = g.inEdges(vert);
      Graph::print(in);

    } else if (option == 6) {
      //Depth First Search
      int dest;
      cout << "What is your destination for your Depth First Search? ";
      cin >> dest;
      list<int> path = g.DFS(dest);
      Graph::print(path);

    } else if (option == 7) {
      //Breadth First Search
      int dest;
      cout << "What is your destination for your Breadth First Search? ";
      cin >> dest;
      g.BFS(dest);     
      
    } else if (option == 8) {
      cout << "Goodbye" << endl;
      looper = false;
      
    } else {
      cout << "Invalid input, please select a value 1-8" << endl;
    }
  }
}

int main() {
  eventLoop();
	//test();

  return 0;
}