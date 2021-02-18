#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Node {

	public:
	
	pair<int,int> p;
	int key;
	Node* left;
	Node* right;
	Node** parent;
	
	Node(int k = 0, Node* l = nullptr, Node* r = nullptr, Node** p = nullptr, pair<int,int> para = make_pair(0,0)) : 
																key(k) , left(l), right(r), parent(p), p(para) {}
	
	bool is_leaf() {
		return left == nullptr && right == nullptr;
	}
	
};


class BinTree {
	
	private:
	
	int size = 0;
	Node* pTree;
	
	public:
	
	int Size() { return this -> size; }
	
	Node* root = nullptr;
	
	BinTree() { this -> pTree = nullptr; }
	
	bool is_empty() { return pTree == nullptr; }
	bool push(int key); 
	bool right_del_by_key(int key);
	
};

void preorder(Node* q, int*& pM);
void inorder(Node* q,vector<int>& is_bst);
void postorder(Node* q);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main() {
	
	BinTree T;
	
	ifstream fin("tst.in");
	int key;
	while (!fin.eof()) {
		fin >> key;
		T.push(key);
	}
	fin.close();
	
	int M = 0;
	int *pM = &M;
	postorder(T.root);
	preorder(T.root,pM);
	cout << *pM;
	
	
	
	ofstream fout("tst.out");
	fout.close();
	
	return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void postorder(Node* q) {
	
	if (q == nullptr)
		return;
	postorder(q -> left);
	postorder(q -> right);
	
	if (q -> left == nullptr xor q -> right == nullptr) {
		
		if (q -> left) {
			Node* left = q -> left;
			q -> p.first = left -> p.first + 1;
		}

		else {
			Node* right = q -> right;
			q -> p.first = q -> right -> p.first + 1;
		}
			
		q -> p.second = q -> p.first;
		
	}
	
	else if (q -> left and q -> right) {
		Node* left = q -> left;
		Node* right = q -> right;
		q -> p.first = max(left -> p.first,right -> p.first) + 1;
		q -> p.second = left -> p.first + right -> p.first + 2;
	}
	
	
	
}






void preorder(Node* q, int*& pM) {		
	if (q == nullptr) 
		return;
		
	if (*pM > q -> p.second)
		*pM = q -> p.second;
		
	preorder(q -> left,pM);
	preorder(q -> right,pM);
}
	

void inorder(Node* q,vector<int>& is_bst) {
	if (q == nullptr)
		return;
		
	inorder(q -> left,is_bst);
	is_bst.push_back(q -> key);
	inorder(q -> right,is_bst);
}

bool BinTree::push(int key) {
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
	
bool BinTree::right_del_by_key(int key) {
		
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