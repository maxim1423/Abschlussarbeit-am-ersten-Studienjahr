#include<iostream>
#include"List.cpp"
using namespace std;
#include<string>
class Vertex {
public:
	string name_station;
	Vertex(string name_station = "") {
		this->name_station = name_station;
	}
};
template<typename T>
class Graph {
public:
	Graph(int quantity_station);
	void addVertex(int number, string name_station);
	void removeVertex(int number);
	void addEdge(int a, int b, int weight);
	void removeEdge(int a, int b);
	void addTwodirectionEdge(int a, int b, int weight);
	void removeTwodirectionEdge(int a, int b);
	void DFS(int number_vertex);
	void BFS(int number_vertex);
	void PrintWay();
	int* djkstra(int number_start_station);

private:

	int quantity_vertex;
	int** connection_matrix;
	Vertex* stations;
};


template<typename T>
Graph<T>::Graph(int quantity_station)
{
	quantity_vertex = quantity_station;
	stations = new Vertex[quantity_station];
	connection_matrix = new  int* [quantity_station];
	for (int i = 0; i < quantity_station; i++) {
		connection_matrix[i] = new int[quantity_station];
		for (int j = 0; j < quantity_station; j++) {
			connection_matrix[i][j] = 0;
		}
	}
}

template<typename T>
void Graph<T>::addVertex(int number, string name_station)
{
	stations[number] = Vertex(name_station);
}

template<typename T>
void Graph<T>::removeVertex(int number)
{
	stations[number] = NULL;
	for (int i = 0; i < quantity_vertex; i++) {
		connection_matrix[i][number] = 0;
		connection_matrix[number][i] = 0;
	}
}

template<typename T>
void Graph<T>::addEdge(int first, int second, int weight)
{
	connection_matrix[first][second] = weight;
}

template<typename T>
void Graph<T>::removeEdge(int first, int second)
{
	connection_matrix[first][second] = 0;
}

template<typename T>
void Graph<T>::addTwodirectionEdge(int a, int b, int weight)
{
	connection_matrix[a][b] = weight;
	connection_matrix[b][a] = weight;
}

template<typename T>
void Graph<T>::removeTwodirectionEdge(int a, int b)
{
	connection_matrix[a][b] = 0;
	connection_matrix[b][a] = 0;
}

template<typename T>
void Graph<T>::DFS(int start_station)
{
	bool* visited_station = (bool*)calloc(quantity_vertex, sizeof(bool));
	List<int> visited_station_list;
	visited_station_list.push_front(start_station);
	visited_station[start_station] = 1;
	while (visited_station_list.Size != 0) {
		int current_station = visited_station_list.GetDataFirst();
		cout << stations[current_station].name_station << " - ";
		visited_station_list.pop_front();
		for (int i = 0; i < quantity_vertex; i++) {
			if (connection_matrix[current_station][i] != 0 && visited_station[i] == 0) {
				visited_station_list.push_front(i);
				visited_station[i] = 1;
			}
		}

	}
	cout << endl;
	free(visited_station);

}

template<typename T>
void Graph<T>::BFS(int start_station)
{
	bool* visited_station = (bool*)calloc(quantity_vertex, sizeof(bool));
	List<int> visited_station_list;
	visited_station_list.push_back(start_station);
	visited_station[start_station] = 1;
	while (visited_station_list.Size != 0) {
		int current_station = visited_station_list.GetDataFirst();
		cout << stations[current_station].name_station << " - ";
		visited_station_list.pop_front();
		for (int i = 0; i < quantity_vertex; i++) {
			if (connection_matrix[current_station][i] != 0 && visited_station[i] == 0) {
				visited_station_list.push_back(i);
				visited_station[i] = 1;
			}
		}

	}
	cout << endl;
	free(visited_station);
}

template<typename T>
void Graph<T>::PrintWay()
{
	cout << "Station connections:" << endl;
	for (int i = 0; i < quantity_vertex; i++) {
		cout << i << ")" << stations[i].name_station << " : ";
		for (int j = 0; j < quantity_vertex; j++) {
			if (connection_matrix[i][j] != 0) {
				cout << stations[j].name_station << " for " << connection_matrix[i][j] << "  ";
			}
		}
		cout << endl;
	}
}

template<typename T>
int* Graph<T>::djkstra(int number_start_station)
{
	int* Minimal_weight_ways = new int[quantity_vertex];
	bool* visited_vertex = new bool[quantity_vertex];
	for (int i = 0; i < quantity_vertex; i++) {
		Minimal_weight_ways[i] = INT_MAX;
		visited_vertex[i] = 0;
	}
	Minimal_weight_ways[number_start_station] = 0;
	for (int i = 0; i < quantity_vertex - 1; i++) {
		int min = INT_MAX;
		int min_Number;
		for (int j = 0; j < quantity_vertex; j++) {
			if (!visited_vertex[j] && Minimal_weight_ways[j] <= min) {
				min = Minimal_weight_ways[j];
				min_Number = j;
			}
		}
		visited_vertex[min_Number] = true;
		for (int k = 0; k < quantity_vertex; k++) {
			if (!visited_vertex[k] && connection_matrix[min_Number][k] != 0 && Minimal_weight_ways[min_Number] != INT_MAX && Minimal_weight_ways[k] > Minimal_weight_ways[min_Number] + connection_matrix[min_Number][k]) {
				Minimal_weight_ways[k] = Minimal_weight_ways[min_Number] + connection_matrix[min_Number][k];
			}
		}
	}
	return Minimal_weight_ways;
}

