#include<iostream>
#include<string>
#include<fstream>
#include"List.cpp"
#include"BinaryTree.cpp"
#include"Graph.cpp"
using namespace std;



void main()
{
	/*
	Für Gabriel

	Im Programm wurde den Dijkstra-Algoritmus benutzt.
	 
	Die Idee ist, dass es eine Menge U-Bahnstationen gibt,an denen sich ein Geschäft mit bestimen Produkten befindet.

	Die Hauptaufgabe des Programms ist, 
	einen kürzsten Weg zwischen die Stationen zu finden, an dem man einen Produkt, den er braucht, kaufen könnte.(Dijkstra-Algoritmus) 

	Es gab auch die zusätzliche Forderungen zum Programm und zwar
	den selbstgeschriebenen List und BinaryTree(ohne Anwendung von Bibliothekfunk.),
	DFS und BFS des Graphs zu definieren(dafür wällt man erst mal die Startstation)
	und eine Verbindung zwischen Stationen zu unterbrechen.

	*/


	string path = "D:\\kyrsova.TXT";
	ifstream fin;
	fin.open(path);// Відкриваємо файл ТХТ
	if (!fin.is_open()) {
		cout << "Error opening file!!";
	}
	List<string> list_product;
	string product;
	//Завантажую список продуктів з файлу
	cout << "Products:" << endl;
	for (int i = 0; i < 11; i++) {
		product = "";
		getline(fin, product);
		cout << product << ", ";
		list_product.push_back(product);

	}
	cout << endl;
	int quantity_station;
	fin >> quantity_station;
	string products;
	string shops;
	string* stations = new string[quantity_station];
	BinaryTree<string> shops_on_station;
	List<string>* products_in_shop = new List<string>[quantity_station];
	Graph<string> map(quantity_station);
	getline(fin, shops);
	//Завантажую наявність продуктів в різних магазинах
	for (int i = 0; i < quantity_station; i++) {


		getline(fin, shops);
		stations[i] = shops;
		for (int j = 0; j < 2; j++) {
			products = "";
			getline(fin, products);
			products_in_shop[i].push_back(products);
		}

		shops_on_station.pushNode(shops, products_in_shop[i]);
		map.addVertex(i, shops);


	}

	string weight;
	string first;
	string second;
	// Завантажую ребра між вершинами графу та їх вагу
	while (!fin.eof()) {
		first = "";
		second = "";
		weight = "";
		getline(fin, first);
		if (first == "endedge") break;
		getline(fin, second);
		getline(fin, weight);
		map.addTwodirectionEdge(stoi(first), stoi(second), stoi(weight));

	}
	fin.close();
	shops_on_station.printTree(shops_on_station.root);
	cout << endl;
	// Друк шляхів графу
	map.PrintWay();
	int starting_station;
	cout << endl;
	cout << "Enter the number of your starting metro station: ";
	cin >> starting_station;
	cout << "DFS:" << endl;
	map.DFS(starting_station);
	cout << "BFS:" << endl;
	map.BFS(starting_station);

	
	//Емуляція розриву ребра
	cout << endl;
	cout << "Select two vertices to break an edge between them:";
	int first_vertex;
	int second_vertex;
	cin >> first_vertex;
	cin >> second_vertex;
	map.removeTwodirectionEdge(first_vertex, second_vertex);

	
	// Друк шляхів після розриву
	map.PrintWay();
	//Замовлення користувача маршруту для покупки продукту(викоритсання алгоритму Дейкстрі)
	while (true) {
		cout << endl;
		cout << "List of products:";
		cout << endl;
		list_product.printList();
		cout << endl;
		cout << endl;
		cout << "What product do you need:";
		string choose_product;
		cin >> choose_product;
		if (!list_product.Exist_element(choose_product)) {
			cout << "This product not found in shops";
			break;
		}
		cout << endl;
		cout << "Station:";
		for (int i = 0; i < quantity_station; i++) {
			cout << stations[i] << "\t";
		}
		cout << endl;
		cout << endl;
		cout << "Choose your station:";
		cout << endl;
		string choose_station;
		cin >> choose_station;
		int number_choose_station = -1;
		for (int i = 0; i < quantity_station; i++) {
			if (stations[i] == choose_station) {
				number_choose_station = i;
				break;
			}
		}
		if (number_choose_station == -1) {
			cout << "Station name entered incorrectly";
		}
		int* minimal_weight_way = map.djkstra(number_choose_station);
		int min_weight = INT_MAX;
		int min_weight_station = 0;
		for (int i = 0; i < quantity_station; i++) {
			if (products_in_shop[i].Exist_element(choose_product) && minimal_weight_way[i] < min_weight) {
				min_weight = minimal_weight_way[i];
				min_weight_station = i;
			}
		}
		cout << endl;
		cout << "You have to go from " << choose_station << " to " << stations[min_weight_station] << " for buy " << choose_product << ".It takes " << min_weight << " minutes" << endl;
		cout << "Do you need to buy something else?" << endl << "Yes - enter '1'" << endl << "No - enter'0'" << endl;
		int choose;
		cin >> choose;
		if (choose == 0) {
			break;
		}
	}
}
