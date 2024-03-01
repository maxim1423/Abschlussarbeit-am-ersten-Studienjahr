#pragma once
#include<iostream>
using namespace std;
template<typename T>
class Node
{
public:
	Node* pNext;
	T data;

	Node(T data = T(), Node* pNext = nullptr)
	{
		this->data = data;
		this->pNext = pNext;
	}
};
template<typename T>
class List
{
public:
	List();
	


	void pop_front();


	void push_back(T data);


	void clear();


	int GetSize() { return Size; }

	T GetDataFirst() { return head->data; }


	void push_front(T data);


	void removeAt(int index);


	void pop_back();

	void printList();

	bool Exist_element(T data);


	int Size;
	Node<T>* head;
};


template<typename T>
List<T>::List()
{
	Size = 0;
	head = nullptr;
}





template<typename T>
void List<T>::pop_front()
{
	Node<T>* temp = head;

	head = head->pNext;

	delete temp;

	Size--;

}

template<typename T>
void List<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
	}
	else
	{
		Node<T>* current = this->head;

		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Node<T>(data);

	}

	Size++;
}

template<typename T>
void List<T>::clear()
{

	while (Size)
	{
		pop_front();
	}
}




template<typename T>
void List<T>::push_front(T data)
{
	head = new Node<T>(data, head);
	Size++;
}



template<typename T>
void List<T>::removeAt(int index)
{
	if (index == 0)
	{
		pop_front();
	}
	else
	{
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}


		Node<T>* toDelete = previous->pNext;

		previous->pNext = toDelete->pNext;

		delete toDelete;

		Size--;
	}

}

template<typename T>
void List<T>::pop_back()
{
	removeAt(Size - 1);
}

template<typename T>
void List<T>::printList()
{
	Node<T>* current = head;

	if (current == nullptr) {
		cout << "This list is empty";
	}
	else {
		while (current != nullptr) {
			cout << current->data << "  ";
			current = current->pNext;
		}

	}
}

template<typename T>
bool List<T>::Exist_element(T data)
{
	Node<T>* current = head;
	while (current != nullptr) {
		if (current->data == data) {
			return true;
		}
		current = current->pNext;
	}
	return false;
}
