#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Node {
	public:
	Node* left;
	Node* right;
	Node* parent;
	int key;
	
	Node(int k = 0, Node* l = nullptr, Node* r = nullptr) : key(k) , left(l), right(r) {}
	
	bool is_leaf() {
		return left == nullptr && right == nullptr;
	}
};

class BinTree {
	
	private:
	
	int size = 0;
	Node* pTree;
	
	public:
	
	int Size() {
		return this -> size;
	}
	Node* root = nullptr;
	
	BinTree() {
		this -> pTree = nullptr;
	}
	
	bool is_empty() {
		return pTree == nullptr;
	}
	
	bool push (int key) {
		root = pTree;
		Node** pp = &pTree;
		Node* p = pTree;

		while (p) {
			
			if (key < p -> key) {
				pp = &(p->left);
				p = p -> left;
			}
			
			else if (key > p -> key) {
				pp = &(p -> right);
				p = p -> right;
			}
			
			else {
				return false;
			}
			
		}
		
		*pp = new Node(key);
		size++;
		return true;
		
	}
	
	void preorder(Node* node,vector<int>& V) {
		
		if (node == nullptr) 
			return;
			
		V.push_back(node -> key);
		
		preorder(node -> left,V);
		preorder(node -> right,V);
	} 
	
};

int main() {
	
	BinTree T;
	
	ifstream fin("input.txt");
	
	int x;
	
	while(!fin.eof()) {
		fin >> x;
		T.push(x);
	}
	
	
	
	fin.close();
	
	vector<int> V;
	
	T.preorder(T.root,V);
	
	ofstream fout("output.txt");
	
	for (int i = 0; i < V.size(); i++) {
		fout << V[i] << '\n';
	}
	
	return 0;


}