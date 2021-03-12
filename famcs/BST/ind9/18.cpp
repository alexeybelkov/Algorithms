#include <iostream>
#include <fstream>
#include <stack>
#include <algorithm>
#include <vector>
#define int long long

using namespace std;

class Node {
	public:
	
	int A;
	int B;
	int key;
	Node* left;
	Node* right;
	Node** parent;
	pair<int,int> p;
	//pair<int,int> g;
	
	Node(int k = 0, Node* l = nullptr, Node* r = nullptr, Node** p = nullptr, pair<int,int> def_p_pair = make_pair(0LL,1), /*pair<int,int> def_g_pair = make_pair(0,0),*/ int b = 0LL, int a = 0LL) : key(k) , left(l), right(r), parent(p), p(def_p_pair),/*g(def_g_pair),*/ B(b), A(a) {}
	
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
	void replace(Node* parent, Node* q, Node* v);
	
};


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
		
	if (size == 0) {
		*pp = new Node(key);
	}
		
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
				size--;
				return true;
			}
			
		}
		
		return false;
		
}

int count_h_l_visit(Node* q, int M) { // return MSL(v)
	
	if (q -> is_leaf()) {
		q -> p.first = 0LL;
		q -> p.second = 1;
	}
	
	else if (q -> left != nullptr and q -> right != nullptr) {
		
		q -> p.first = max(q -> left -> p.first, q -> right -> p.first) + 1;
		
		if (q -> left -> p.first - q -> right -> p.first != 0LL) {
			
			if (q -> left -> p.first > q -> right -> p.first) {
				q -> p.second = q -> left -> p.second;
			}
			
			else {
				q -> p.second = q -> right -> p.second;
			}
			
		}
		
		else {
			q -> p.second = q -> left -> p.second + q -> right -> p.second;
		}
		
		if (q -> left -> p.first + q -> right -> p.first + 2 > M) {
			M = q -> left -> p.first + q -> right -> p.first + 2;
		}
		
	}
	
	else {
		
		if (q -> left) {
			
			q -> p.first = q -> left -> p.first + 1;
			q -> p.second = q -> left -> p.second;
			
		}
		
		else {
			
			q -> p.first = q -> right -> p.first + 1;
			q -> p.second = q -> right -> p.second;
			
		}
		
		if (q -> p.first > M) {
			M = q -> p.first;
		}
		
	}
	
	return M;
	
}

void count_h_l(Node* q,int& M) { //postorder
	
	stack<Node*> S;
	Node* last_node_visited = nullptr;
	
	while (!S.empty() or q != nullptr) {
		if (q != nullptr) {
			S.push(q);
			q = q -> left;
		}
		
		else {
			
			Node* peek_node = S.top();
			
			if (peek_node -> right != nullptr and last_node_visited != peek_node -> right) {
				q = peek_node -> right;
			}
			
			else {
				M = count_h_l_visit(peek_node,M);
				last_node_visited = S.top();
				S.pop();
			}
			
		}
		
	}
}

void count_B_visit(Node* q, int M) {
	
	if (q -> is_leaf()) {}
	
	else if (q -> left != nullptr and q -> right != nullptr) {
		
		if (q -> left -> p.first + q -> right -> p.first + 2 == M) {
			q -> B = q -> left -> p.second * q -> right -> p.second;
		}
		
		else {
			q -> B = 0LL;
		}
		
	}
	
	else {
		
		if (q -> left) {
			if (q -> p.first == M) {
				q -> B = q -> left -> p.second;
			}
		}
		
		else if (q -> right) {
			if (q -> p.first == M) {
				q -> B = q -> right -> p.second;
			}
		}
		
		else {
			q -> B = 0LL;
		}
		
	}
	
}

void count_B(Node* q, int M) {
	
	if (q == nullptr) {
		return;
	}
	
	stack<Node*> S;
	S.push(q);
	
	while (!S.empty()) {
		
		q = S.top();
		
		count_B_visit(q, M);
		
		S.pop();
		
		if (q -> right) {
			S.push(q -> right);
		}
		
		if (q -> left) {
			S.push(q -> left);
		}
	}
	
}

void count_paths(Node* q) {
	if (q == nullptr) {
		return;
	}
	
	if (q -> parent == nullptr) {
		q -> A = 0LL;
	}
	
	stack<Node*> S;
	S.push(q);
	
	while (!S.empty()) {
		
		q = S.top();
		
		
		if (q -> left and q -> right) {
			if (q -> left -> p.first - q -> right -> p.first != 0LL) {
				
				if (q -> left -> p.first > q -> right -> p.first) {
					q -> left -> A = q -> A  + q -> B;
					q -> right -> A = q -> B;
				}
				
				else {
					q -> right -> A = q -> A + q -> B;
					q -> left -> A = q -> B;
				}
			}
			
			else {
				q -> left -> A = q -> B + q -> left -> p.second*(q -> A / q -> p.second);
				q -> right -> A =  q -> B + q -> right -> p.second * (q -> A / q -> p.second);
			}
			
		}
		
		else if (q -> left != nullptr xor q -> right != nullptr) {
			
			if (q -> left) {
				q -> left -> A = q -> A + q -> B;
			}
			
			else {
				q -> right -> A = q -> A + q -> B;
			}
			
		}
		
		S.pop();
		
		if (q -> right != nullptr) {
			S.push(q -> right);
		}
		
		if (q -> left != nullptr) {
			S.push(q -> left);
		}
		
	}
	
	
}

void preorder_out_tree(Node* q,ofstream& fout) {
	
	if (q == nullptr) {
		cout << "nullptr after delete";
	}
	
	stack<Node*> S;
	S.push(q);
	
	while (!S.empty()) {
		
		q = S.top();
		fout << q -> key << "\n";
		S.pop();
		
		if (q -> right) {
			S.push(q -> right);
		}
		
		if (q -> left) {
			S.push(q -> left);
		}
		
	}
	
}

void find_verteces(Node* q, vector<int>& V) {
	
	if (q == nullptr) {
		return;
	}
	
	stack<Node*> S;
	S.push(q);
	
	while (!S.empty()) {
		
		q = S.top();
		
		if ( (q -> A + q -> B) % 2 == 0LL and ( q -> A + q -> B) > 1) {
			V.push_back(q -> key);
		}
		
		S.pop();
		
		if (q -> right) {
			S.push(q -> right);
		}
		
		if (q -> left) {
			S.push(q -> left);
		}
		
	}
	
}

int32_t main() {
	
	BinTree T;
	ifstream fin("tst.in");
	
	while (!fin.eof()) {
		int x;
		fin >> x;
		T.push(x);
	}
	
	fin.close();
	
	vector<int> V;
	
	int M = 0LL;
	count_h_l(T.root,M);
	count_B(T.root,M);
	count_paths(T.root);
	find_verteces(T.root,V);
	
	if (V.size()) {
		int min = V[0];
		for (int i = 0; i < V.size(); i++) {
			if (V[i] < min) {
				min = V[i];
			}
		}

		T.right_del_by_key(min);
	}
	
	ofstream fout("tst.out");
	preorder_out_tree(T.root, fout);
	
	return 0;
}