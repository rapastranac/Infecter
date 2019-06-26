#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
void addEdge(vector< vector<int> > &adj, int u, int v);
void readGraph(vector< vector<int> > &adj, int V);
void printGraph(vector< vector<int> > adj, int V);
int infecter(vector< vector<int> > &adj, vector<bool> &Z, int V);

int main()
{
	const int V = 14;
	vector< vector<int> > adj;
	vector<bool> Z;
	int k;	//times units
	adj.resize(V);
	Z.resize(V);
	Z[0] = true;
	Z[7] = true;
		
	readGraph(adj,V);
	k = infecter(adj, Z, V);
	printGraph(adj, V);
	printf("Time units required to infect all the cities = %d", k);

	return 0;
}

void addEdge(vector< vector<int> > &adj, int u, int v)
{
	adj[u].push_back(v);
	adj[v].push_back(u);
}
void printGraph(vector< vector<int> >adj, int V)
{
	for (int i = 0; i < V; ++i)
	{
		printf("\n Adjacency list of vertex %d \n point at ",i);

		for (auto j : adj[i])
			printf("-> %d",j);
		printf("\n");
	}
}
void readGraph(vector< vector<int> > &adj, int V)
{
	ifstream inFile;
	inFile.open("edges.txt");
	int u;
	int v;
	//Read edges from file

	if (!inFile) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}
	while (true)
	{
		if (inFile.eof()) break;
		inFile >> u;
		inFile >> v;
		addEdge(adj, u, v);
	}
	inFile.close();
}
int infecter(vector< vector<int> > &adj, vector<bool> &Z, int V)
{
	vector<bool> Nx(V);
	int sum = 0;
	int k = 0;
	//Add neighbours of current vertexes to Z
	for (int i = 0; i < V; i++)
	{
		if (Z[i])
		{
			Nx[i] = true;
			sum++;
			for (auto x : adj[i]) {
				Nx[x] = true;
			}
		}
	}
	if (sum < V) {
		k = infecter(adj, Nx, V);
		k++;
	}
	return k;
}