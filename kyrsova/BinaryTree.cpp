#include<iostream>
using namespace std;
#include <string>
#include "List.cpp"
template<typename T>
class TreeNode {
public:
	string key;
	List<T> data;
	TreeNode<T>* right;
	TreeNode<T>* left;
	TreeNode(List<T> data, string key = "") {
		this->key = key;
		this->data = data;
		right = nullptr;
		left = nullptr;
	}
};
template<typename T>
class BinaryTree
{

public:
	TreeNode<T>* root;
	BinaryTree() {
		root = nullptr;
	}

	void pushNode(string key, List<T> data);
	void printTree(TreeNode<T>* Node);
	TreeNode<T>* GetRoot() { return root; };
	TreeNode<T>* GetNode(string key);






};

template<typename T>
void BinaryTree<T>::pushNode(string key, List<T> data)
{
	TreeNode<T>* element = new TreeNode<T>(data, key);
	if (root == nullptr) {
		root = element;
	}
	else {
		TreeNode<T>* current_root = root;

		while (true) {

			if (key < current_root->key) {

				if (current_root->left == nullptr) {
					current_root->left = element;
					break;
				}
				else {
					current_root = current_root->left;
				}
			}
			else {

				if (current_root->right == nullptr) {
					current_root->right = element;
					break;
				}
				else {
					current_root = current_root->right;
				}
			}
		}
	}
}

template<typename T>
void BinaryTree<T>::printTree(TreeNode<T>* Node)
{
	if (Node->left != nullptr) {
		printTree(Node->left);
	}
	cout << Node->key << " shop: ";
	Node->data.printList();
	cout << endl;

	if (Node->right != nullptr) {
		printTree(Node->right);
	}

}
template<typename T>
TreeNode<T>* BinaryTree<T>::GetNode(string key)
{
	TreeNode<T>* current_root = root;
	if (key.empty() || root == nullptr) return root;
	while (key.compare(current_root->key) != 0) {
		if (key.compare(current_root->key) == -1) {
			current_root = current_root->left;
		}
		else {
			current_root = current_root->right;
		}
		if (current_root == nullptr) {
			return nullptr;
		}

	}
	return current_root;
}
