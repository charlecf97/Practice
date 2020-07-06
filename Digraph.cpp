// ConsoleApplication3.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Christian Charles

#include <iostream>
#include <string>

using namespace std;

class node {
public:
	int vertex;
	node* next;
};

class Digraph {
private:

	node* Header;
	int size; //number of vertices
	node* stack;

	void RecursiveDelete(node* temp) {
		if (temp == NULL)
			return;
		RecursiveDelete(temp->next);
		delete temp;
		temp = NULL;
		return;
	}

	void StackPush(int x) {
		// add x to the stack
		node* temp = new node;
		temp->vertex = x;
		temp->next = stack;
		stack = temp;
		return;
	}

	bool StackContains(int x) {
		// check if stack contain vertex x
		node* temp = stack;
		while (temp != NULL) {
			if (temp->vertex == x)
			{
				cout << "\nERROR: Digraph is cyclic\n";
				return true;
			}
			temp = temp->next;
		}
		return false;
	}

	void StackPop() {
		// remove top element element from stack
		node* temp = stack;
		if (temp == NULL)
			return;
		stack = stack->next;
		delete temp;
		return;
	}
public:


	Digraph(int s) {  //constructor
		//create array of node which Header points to, and initialize each node
		Header = new node[s];
		size = s;
		for (int i = 0; i < size; i++) {
			Header[i].vertex = i;
			Header[i].next = NULL;
		}

	}

	~Digraph() {
		//delete pointers
		for (int i = 0; i < size; i++)
		{
			RecursiveDelete(&Header[i]);
		}
	}

	void addEdge(int x, int y) {
		//add Edge to digraph, task x must preced task y
		node* nextNode = Header[x].next;
		node* newEdge = new node;
		newEdge->vertex = y;
		newEdge->next = nextNode;
		Header[x].next = newEdge;
	}

	void deleteEdge(int x, int y) {
		//delete edge
		node* prev = &Header[x];
		node* ptr = Header[x].next;

		while (ptr != NULL && ptr->vertex != y) {
			prev = ptr;
			ptr = ptr->next;
		}
		if (ptr == NULL)
			cout << "edge does not exist. \n";
		else {
			if (ptr->next == NULL)
				prev->next = NULL;
			else
				prev->next = ptr->next;
			delete ptr;
		}

	}

	bool TopologicalSort(int* TopList) {
		int* Mark = new int[size];
		for (int i = 0; i < size; i++) {
			Mark[i] = 0;
		}
		int counter = size - 1;
		for (int i = 0; i < size; i++) {
			if (Mark[i] == 0) {
				stack = NULL;
				//execute a depth first search for each path starting at i
				bool cycl = DFS(i, Mark, TopList, &counter);
				if (cycl) return true;
			}

		}
		return false;
	}

	bool DFS(int i, int* Mark, int* TopList, int* counter) {
		Mark[i] = 1;
		bool cycl = StackContains(i);
		if (cycl)
			return true;

		StackPush(i);

		node* ptr = Header[i].next;
		while (ptr != NULL) {
			if (StackContains(ptr->vertex))
				return true;
			if (Mark[ptr->vertex] == 0)
			{
				bool cycl = DFS(ptr->vertex, Mark, TopList, counter);
				if (cycl) return true;
			}
			ptr = ptr->next;
		}
		TopList[*counter] = i;
		*counter = *counter - 1;
		StackPop();
		return false;
	}

	int inrange(char x[]) {

		if (isdigit(x[0]) == 0 || atoi(x) < 0 || atoi(x) >= size) {
			cout << "\nTask entered doesn't exist, only enter the number of the task: ";
			cin >> x;

		}
		return atoi(x);
	}
};


int main()
{
	cout << "Hello! Lets make a Digraph!\n";
	cout << "How many different tasks would you like to do? ";
	int size;
	cin >> size;
	Digraph graph(size);
	string* tasks = new string[size];
	cout << "Enter the names of your tasks: \n";

	cin.ignore();

	for (int i = 0; i < size; i++)
	{
		cout << i << ". ";

		string task;
		getline(cin, task);
		tasks[i] = task;
	}
	int option = 0;
	while (option != 4) {
		cout << "Options: \n1. add edge\n2. delete edge\n3. Topological Sort\n4. quit\nChoice:  ";
		cin >> option;

		char xcheck[4], ycheck[4];
		int x, y;
		if (option == 1) {
			cout << "Enter order relation in the form 'x y': ";
			cin >> xcheck;
			x = graph.inrange(xcheck);
			cin.ignore();
			cin >> ycheck;
			y = graph.inrange(ycheck);
			graph.addEdge(x, y);
		}
		else if (option == 2)
		{
			cout << "Enter order relation in the form 'x y': ";
			cin >> xcheck;
			x = graph.inrange(xcheck);
			cin.ignore();
			cin >> ycheck;
			y = graph.inrange(ycheck);
			graph.deleteEdge(x, y);
		}
		else if (option == 3) {
			int* TopList = new int[size];
			bool cycl = graph.TopologicalSort(TopList);
			if (cycl == false) {
				cout << "Topological Order:\n";
				for (int i = 0; i < size; i++) {
					cout << TopList[i] << ". " << tasks[TopList[i]] << "\n";
				}
				cout << "\n";
			}
		}

	}

	return 0;
}
