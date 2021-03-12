#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>

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
	
	Node(int k = 0, Node* l = nullptr, Node* r = nullptr, Node** p = nullptr, pair<int,int> def_p_pair = make_pair(0,1), /*pair<int,int> def_g_pair = make_pair(0,0),*/ int b = 0, int a = 0) : 
																key(k) , left(l), right(r), parent(p), p(def_p_pair),/*g(def_g_pair),*/ B(b), A(a) {}
	
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

void BinTree::replace(Node* prev, Node* q, Node* v) {
	if (prev == nullptr) {
		root = v;
	}
	
	else if (prev -> left == q) {
		prev -> left = v;
	}
	
	else if (prev -> right == q) {
		prev -> right = v;
	}
}

void cout_h_L(Node* q, int& M) {
	
	if (q -> is_leaf()) {
		q -> p.first = 0;
		q -> p.second = 1;
	}
	
	else if (q -> left == nullptr xor q -> right == nullptr) {
		
		if (q -> left != nullptr) {
			q -> p.first = q -> left -> p.first + 1;
			q -> p.second = q -> left -> p.second;
			if (q -> left -> p.first + 1 > M) {
				M = q -> left -> p.first + 1;
			}
		}
		
		else {
			q -> p.first = q -> right -> p.first + 1;
			q -> p.second = q -> right -> p.second;
			if (q -> right -> p.first + 1 > M) {
				M = q -> right -> p.first + 1;
			}
		}
	}
	
	else {
		q -> p.first = max(q -> left -> p.first, q -> right -> p.first) + 1;
		
		if (q -> left -> p.first > q -> right -> p.first) {
			q -> p.second = q -> left -> p.second;
		}
		
		else if (q -> left -> p.first < q -> right -> p.first) {
			q -> p.second = q -> right -> p.second;
		}
		
		else {
			q -> p.second = q -> left -> p.second + q -> right -> p.second;
		}
		
		if (q -> left -> p.first + q -> right -> p.first + 2 > M) {
			M = q -> left -> p.first + q -> right -> p.first + 2;
		}
		
	}
	
	
}

void postorder_for_count_h_L(Node* q,int& M) {
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
				cout_h_L(peek_node,M);
				last_node_visited = S.top();
				S.pop();
			}
		}
	}
}

void preorder(Node* q, int& M) {
	
	if (q == nullptr) {
		return;
	}
	
	
	stack<Node*> S;
	S.push(q);
	
	while (!S.empty()) {
		
		q = S.top();
		
		if (q -> left == nullptr xor q -> right == nullptr) {
			
			if (q -> left) {
				
				if (M == q -> left -> p.first + 1) {
					q -> B = q -> left -> p.second;
				}
				
			}
			
			else {
				
				if (M == q -> right -> p.first + 1) {
					q -> B = q -> right -> p.second;
				}
				
			}
			
		}
		
		else if (q -> left and q -> right) {
			
			if (M == q -> left -> p.first + 2 + q -> right -> p.first) {
				q -> B = q -> left -> p.second * q -> right -> p.second;
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
	
	return;
	
}


void postorder_visit(Node* q, int& M) {
	
	//if (q == nullptr)
		//return;
		
	//postorder(q -> left, M);
	//postorder(q -> right, M);
	if (q -> left == nullptr xor q -> right == nullptr) {
		
		if (q -> left) {
			q -> p.first = q -> left -> p.first + 1;
			q -> p.second = q -> left -> p.second;
			
			if (q -> left -> p.first + 1 > M) {
				M = q -> left -> p.first + 1;
			}
			
		}

		else {
			q -> p.first = q -> right -> p.first + 1;
			q -> p.second = q -> right -> p.second;
			
			if (q -> right -> p.first + 1 > M) {
				M = q -> right -> p.first + 1;
			}
			
		}
		
	}
	
	else if (q -> left and q -> right) {
		
		q -> p.first = max(q -> left -> p.first,q -> right -> p.first) + 1;
		
		if ( (q -> left -> p.first > q -> right -> p.first) or (q -> left -> p.first < q -> right -> p.first) ) {
			
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
	
	//else {
	//	q -> p.second = 1;
	//}
	
}

void postorder(Node* q, int& M) {
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
				postorder_visit(peek_node,M);
				last_node_visited = S.top();
				S.pop();
			}
			
		}
		
	}
	
	return;
	
}



void count_paths(Node* q,vector<int>& V, int& M) {
	if (q == nullptr)
		return;
		
	stack<Node*> S;
	S.push(q);
	
	while(!S.empty()) {
		
		q = S.top();
		
		if (q -> left == nullptr xor q -> right == nullptr) {
			if (q -> left)
				q -> left -> A = q -> A + q -> B;
				
			else
				q -> right -> A = q -> A + q -> B;
		}
		
		else if (q -> left and q -> right) {
			
			if (q -> left -> p.first > q -> right -> p.first) {
				q -> left -> A = q -> A + q -> B;
				q -> right -> A = q -> B;
			}
			
			else if (q -> left -> p.first < q -> right -> p.first) {
				q -> right -> A = q -> A + q -> B;
				q -> left -> A = q -> B;
			}
			
			else {
				q -> left -> A = q -> B + q -> left -> p.second * (q -> A / q -> p.second);
				q -> right -> A = q -> B + q -> right -> p.second * (q -> A / q -> p.second);
			}
			
		}
		
		if ((q -> A + q -> B) % 2 == 0 and (q -> A + q -> B) > 1)
			V.push_back(q -> key);
		
		cout << q -> key << " : h = " << q -> p.first << " L = " << q -> p.second << "\n  B = " << q -> B << " A = " << q -> A << endl;
		
		S.pop();
		
		if (q -> right)
			S.push(q -> right);
		if (q -> left)
			S.push(q -> left);
	}
	
}


void preorder_out_tree(Node* q, ofstream& fout) {
	
	if (q == nullptr)
		return;
		
	stack<Node*> S;
	S.push(q);
		
	while (!S.empty()) {	
		
		q = S.top();
		fout << q -> key << '\n';
		S.pop();
		
		if (q -> right)
			S.push(q -> right);
		if (q -> left)
			S.push(q -> left);
	}
	
	return;
}
int count_length(Node* q, int M);
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
	
	vector<int> V;
	
	postorder(T.root,M);
	//postorder_for_count_h_L(T.root,M);
    //M = count_length(T.root,M);
	preorder(T.root, M);
	count_paths(T.root,V,M);
	//cout << endl << M << endl;
	if (V.size() > 0) {
	
	int min = V[0];
	//cout << "V : ";
		for (int i = 1; i < V.size(); i++) {
		//	cout << V[i] << ' ';
			if (V[i] < min) {
				min = V[i];
			}
		}
		
		T.right_del_by_key(min);
	//	cout << endl << min;
	}
	
	ofstream fout("tst.out");
	preorder_out_tree(T.root,fout);
	fout.close();
	
	return 0;
}

int count_length(Node* q, int M) {
	
	if (q == nullptr) {
		return 0;
	}
	
	int length = 0;
	
	stack<Node*> S;
	S.push(q);
	
	while(!S.empty()) {
		q = S.top();
		
		if (q -> left == nullptr xor q -> right == nullptr) {
			if (q -> left) {
				if (q -> left -> p.first + 1 == M) {
					length++;
				}
			}
			
			else {
				if (q -> right -> p.first + 1 == M) {
					length++;
				}
			}
		}
		
		else if (q -> left and q -> right) {
			if (q -> left -> p.first + q -> right -> p.first + 2 == M) {
				length++;
			} 
		}
		
		S.pop();
		
		if (q -> right) {
			S.push(q -> right);
		}
		
		if (q -> left) {
			S.push(q -> left);
		}
	}
	
	return length;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
	
		Node* prev = nullptr;
		Node* q = root;
		
		while(true) {
			
			if (q == nullptr) {
				return false;
			}
				
			if (key < q -> key) {
				prev = q;
				q = q -> left;
			}
			
			else if (key > q -> key) {
				prev = q;
				q = q -> right;
			}
			
			else break;
			
		}
		
		Node* result = nullptr;
		
		if (q -> left == nullptr) {
			result = q -> right;
		}
		
		else if (q -> right == nullptr) {
			result = q -> left;
		}
		
		else {
			
			Node* min_node_prev = q;
			Node* min_node = q -> right;
			
			while (min_node -> left != nullptr) {
				min_node_prev = min_node;
				min_node = min_node -> left;
			}
			
			result = q;
			q -> key = min_node -> key;
			
			replace(min_node_prev,min_node,min_node -> right);
		}
		
		replace(prev,q,result);
		
		return true;

	}