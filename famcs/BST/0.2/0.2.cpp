#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Node {

	public:
	Node* left;
	Node* right;
	Node** parent;
	int key;
	
	Node(int k = 0, Node* l = nullptr, Node* r = nullptr,Node** p = nullptr) : key(k) , left(l), right(r), parent(p) {}
	
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
	
	bool push(int key) {
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
		
		if (size == 0)
			*pp = new Node(key);
		
		else {
			Node** parent = pp;
			*pp = new Node(key,nullptr,nullptr,parent);
		}
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
	
	bool left_del_by_key(int key) {
		
		Node* p = pTree;
		
		while (p) {
			
			if (key < p -> key) {
				p = p -> left;
			}
			
			else if (key > p -> key) {
				p = p -> right;
			}
			
			else if (key == p -> key) {
				
				if ( p -> is_leaf() )
					*(p -> parent) = nullptr;
					
				else if (p -> left == nullptr xor p -> right == nullptr) {
					
					if (p -> left) {
						if (p -> parent)
							*(p -> parent) = p -> left;
							
						else {
							pTree = p -> left;
							root = p -> left;
							p -> left -> parent = nullptr;
						}
						
					}
					
					else {
						
						if (p -> parent)
							*(p -> parent) = p -> right;
							
						else {
							pTree = p -> right;
							root = p -> right;
							p -> right -> parent = nullptr;
						}
							
					}
						
				}
				
				else {
					
					Node *pf = p -> right;
					Node *pmin = pf;
					int m = pf -> key;
					
					while (pf) {
						if (pf -> key < m) {
							m = pf -> key;
							pmin = pf;
						}
						pf = pf -> left;
					}
					
					p -> key = pmin -> key;
					
					if (pmin -> is_leaf())
						*(pmin -> parent) = nullptr;
					
					else
						*(pmin -> parent) = pmin -> right;
					
				}
					
				return true;
			}
			
		}
		
		return false;
		
	}
	
};

int main() {
	
	BinTree T;
	ifstream fin("input.txt");
	int x;
	int key_for_delete;
	int i = 0;
	
	while(!fin.eof()) {
		
		if (i == 0)
			fin >> key_for_delete;
		
		
		else if (i == 1);
		
		else {
			fin >> x;
			T.push(x);
		}
		
		i++;
		
	}
	
	fin.close();
	
	T.left_del_by_key(key_for_delete);
	
	vector<int> V;
	ofstream fout("output.txt");
	
	T.preorder(T.root,V);
	
	for (int i = 0; i < V.size(); i++) {
		fout << V[i] << '\n';
	}
	
	fout.close();

	return 0;
	
}