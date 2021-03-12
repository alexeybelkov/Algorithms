#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

class In_vertex {
	
	public:
	
	int m;
	int p;
	char c;
	
	In_vertex(int m, int p, int c) : m(m), p(p), c(c) {}
	
};

class Node {

	public:
	
	int key;
	Node* left;
	Node* right;
	Node* parent;
	
	Node(int k = 0, Node* l = nullptr, Node* r = nullptr, Node* p = nullptr) : key(k) , left(l), right(r), parent(p) {}
	
	bool is_leaf() {
		return left == nullptr && right == nullptr;
	}
	
};

class T {
	public:
	Node* q;
	int min;
	int max;
	T(Node* v = nullptr, int min = -2147483648, int max = 2147483647) : q(v), min(min), max(max) {}
	//T(Node* v = nullptr, /*long long*/int min = -2147483648, int max = 2147483647) : q(v), min(min), max(max) {}
};

void inorder(Node* q,vector<int>& is_bst) {
	
	if (q == nullptr)
		return;
		
	inorder(q -> left,is_bst);
	is_bst.push_back(q -> key);
	inorder(q -> right,is_bst);
	
	
}

bool IsBinSearchTree(Node* q) {
	
	if (q == nullptr)
		return true;
		
	stack<T> S;
	S.push(T(q,-2147483648,2147483647));
	
	while (!S.empty()) {
		q = S.top().q;
		auto min = S.top().min;
		auto max = S.top().max;
		S.pop();
		
		if (q -> key < min or q -> key > max) {
			return false;
		}
		
		if (q -> right) {
			S.push(T(q -> right,q -> key,max));
		}
		
		if (q -> left) {
			S.push(T(q -> left, min, /*(long long)*/(q -> key) - 1));
		}
	}
	
	return true;
	
}

int main() {
	
	vector<In_vertex> Vv;
	
	int i = 0;
	int n;
	ifstream fin("bst.in");

	while (!fin.eof()) {
		
		if (i < 2) {
			
			if (i == 0) {
				fin >> n;
			}
				
			else {
				int m;
				fin >> m;
				Vv.push_back(In_vertex(m,0,'H'));
			}
				
		}
		
		else {
			
			int m;
			int p;
			char c;
		
			fin >> m;
			fin >> p;
			fin >> c;
		
			Vv.push_back(In_vertex(m,p,c));
		
		}
		
		i++;
		
	}
	
	vector<Node> Vn;
	for (int i = 0; i < n; i++)
		Vn.push_back(Node(Vv[i].m));
		
	fin.close();
	ofstream fout("bst.out");
		
	
	for (int i = 1; i < n; i++) {
		if (Vv[i].c == 'L') {
			if (Vn[Vv[i].p - 1].left == nullptr and Vn[Vv[i].p - 1].key > Vn[i].key) {
				Vn[Vv[i].p - 1].left = &Vn[i];
			}
			else {
				fout << "NO";
				return 0;
			}
		}
		else {
			if (Vn[Vv[i].p - 1].right == nullptr and Vn[Vv[i].p - 1].key <= Vn[i].key) {
				Vn[Vv[i].p - 1].right = &Vn[i];
			}
			else {
				fout << "NO";
				return 0;
			}
		}
	}
	
	
	if (IsBinSearchTree(&Vn[0]) == false) {
		fout << "NO";
		return 0;
	}
	
		
	else {
		fout << "YES";
		return 0;
	}
	
	fout.close();
	
	
	
	return 0;
}