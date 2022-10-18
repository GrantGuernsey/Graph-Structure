
#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <iterator>
#include <list>
using namespace std;

class Graph{
private:
	/* ERROR CLASS */
	class Path{};
	class DNE{};

	/* EDGE CLASS */
	class Edge{
	public:
		int data;
		int cost;

		Edge(int d, int c){
			data = d;
			cost = c;
		}

		bool operator == (const Edge& e){
			return this->data == e.data;
		}
	};

	/* VERTEX CLASS */
	class Vertex{
	public:
		int data;
    int count;
		list<Edge> edges;

		Vertex(int d){
			data = d;
		}

		bool operator == (const Vertex& v){
			return this->data == v.data;
		}
	};

	/* LIST OF VERTICIES */
	list<Vertex> vertices;

	/* VERTICES HELPER METHODS */
	bool contains(int id){
		list<Vertex>::iterator itr;
		for (itr = vertices.begin(); itr != vertices.end(); itr++){
			if(itr->data == id) return true;
		}
		return false;
	}
	Vertex* find(int id){
		list<Vertex>::iterator itr;
		for (itr = vertices.begin(); itr != vertices.end(); itr++){
			if(itr->data == id){
				Vertex* retVert = &(*itr);
				return retVert;
			}
		}

		throw DNE();
	}

	/* DFS HELPER METHODS */
	bool contains(list<int> lst, int id){
		list<int>::iterator itr = lst.begin();
		for (itr; itr != lst.end(); itr++){
			if (*itr == id) return true;
		}

		return false;
	}
	list<Vertex>::iterator get(int id){
		list<Vertex>::iterator itr;
		for (itr = vertices.begin(); itr != vertices.end(); itr++){
			if(itr->data == id) return itr;
		}

		throw DNE();
	}

public:
	/* CONTRUCTOR, DESTRUCTOR NOT NEEDED DUE TO STL BEING USED */
	int size;
	Graph(){
		size = 0;
	}

	/* DISPLAY METHOD FOR INT LISTS */
	static void print(list<int> lst){
		if (lst.empty()) cout << "Empty";

		else{
			list<int>::iterator itr;
			for(itr = lst.begin(); itr != lst.end(); itr++){
				cout << *itr << ' ';
			}
		}
		
		cout << endl;
	}

	/* VERTEX METHODS */
	void addVertex(int id){
		Vertex vert(id);
		if (!contains(id)){
			vert.count = size;
			size++;
			vertices.push_back(vert);
		}
	}

	/* EDGE METHODS */
	void addEdge(int from, int to, int cost){
		//Error handling with invalid paths
		if (!contains(from) || !contains(to)) throw Path();

		//Edge creation and insertion
		Edge path(to, cost);
		find(from)->edges.push_back(path);
	}
	void removeEdge(int from, int to){
		//Error handling with invalid paths
		if (!contains(from) || !contains(to)) throw Path();

		//Edge removal
		list<Edge>::iterator itr = find(from)->edges.begin();
		for (itr; itr != find(from)->edges.end(); itr++){
			if (itr->data == to) find(from)->edges.erase(itr);
			break;
		}
	}
	bool hasEdge(int from, int to){
		//Vertex Creation
		if(!contains(from)) return false;
		Vertex v = *find(from);
		
		list<Edge>::iterator itr;
		for (itr = v.edges.begin(); itr != v.edges.end(); itr++){
			if(itr->data == to){
				return true;
			}
		}
		return false;
	}

	list<int> inEdges(int to){
		list<int> retval;
		list<Vertex>::iterator itr;
		for (itr = vertices.begin(); itr != vertices.end(); itr++){
			if(hasEdge(itr->data, to)){
				retval.push_front(itr->data);
			}
		}
		return retval;
  	}
	list<int> outEdges(int from){
		list<int> retval;
		Vertex vert = *find(from);
		list<Edge>::iterator itr;
		for (itr = vert.edges.begin(); itr != vert.edges.end(); itr++){
			retval.push_front(itr->data);
		}
		return retval;
	}

	/* DEPTH FIRST SEARCH */
	list<int> DFS(int dest){
		/* CASE 0: Destination doesn't exist */
		if (!contains(dest)) throw DNE();

		list<int> dead; //Keeps track of visited nodes
		list<int> path; //Keeps track of path
		
		int prev; //Used to get id of previous node in path
		list<int>::iterator back; //Used to backtrack path to get previous node
		list<Edge>::iterator next; //Used to index through edge lists

		//Initialize path
		list<Vertex>::iterator cur = vertices.begin();
		path.push_back(cur->data);

		/* CASE 1: Destination is the first node */
		if (cur->data == dest) return path;

		bool search = true;
		while(search){
			//Move to next node if edge list isn't empty
			if (cur->edges.begin() != cur->edges.end()){

				//Search through edge list for a valid next node
				for (next = cur->edges.begin(); next != cur->edges.end(); next++){

					//A node has been found that hasn't been visited
					if (!contains(path, next->data) && !contains(dead, next->data)){
						//Add to path
						cur = get(next->data);
						path.push_back(cur->data);

						//Check if destination has been reached
						if (cur->data == dest) search = false;
						break;
					}
				}

				//Valid next node not found, move node from path to dead
				if (next == cur->edges.end()){
					path.pop_back();
					dead.push_back(cur->data);

					//Cur is root, return the empty path
					if (cur == vertices.begin()) return path;

					//Cur isn't root -> go back one
					prev = *path.rbegin();
					cur = get(prev);
				}
			}

			//Edge list is empty, move node from path to dead
			else{
				path.pop_back();
				dead.push_back(cur->data);

				//Cur is root, return the empty path
				if (cur == vertices.begin()) return path;

				//Cur isn't root, go back one
				prev = *path.rbegin();
				cur = get(prev);
			}
		}

		return path;
	}
  void BFS(int found){
		list<Vertex> queue;
		bool* explored = new bool[size];
		for(int x = 0; x < size; x++){
			explored[x] = false;
		}
		queue.push_front(vertices.front());
		while(!queue.empty()){
			Vertex v = queue.front();
			cout << v.data << endl;
			queue.pop_front();
			if(v.data == found){
				//cout << found;
				return;
			}
			list<Edge>::iterator itr;
			for (itr = v.edges.begin(); itr != v.edges.end(); itr++){
				Vertex w = *find(itr->data);
				if(!explored[w.count]){ // if its not explored
					explored[w.count] = true; // make it explored 
					queue.push_back(w);
				}
			}
		}
		cout << "Node was never found" << endl;
	}
};

#endif