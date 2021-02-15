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
	
	pair<int,char> key;
	Node* left;
	Node* right;
	Node* parent;
	
	Node(pair<int,char> k = make_pair(0,'Z'), Node* l = nullptr, Node* r = nullptr,Node* p = nullptr) : key(k) , left(l), right(r), parent(p) {}
	
	bool is_leaf() {
		return left == nullptr && right == nullptr;
	}
	
};

void inorder(Node* q,vector<pair<int,char>>& is_bst) {
	
	if (q == nullptr)
		return;
		
	inorder(q -> left,is_bst);
	is_bst.push_back(q -> key);
	inorder(q -> right,is_bst);
	
	
}

 bool check(Node* q, int min = -2147483648, int max = 2147483647) {
	
	if (q == nullptr)
		return true;
		
	pair<int,char> p = q -> key;
	
	if (p.first < min or p.first > max)
		return false;
		
	return check(q->left, min, p.first - 1) and check(q -> right, p.first, max);
		
}

bool IsBinSearchTree(Node* q) {
	return check(q);
}
/*
bool isBST(Node* q, int left_key, int right_key) {
	if (q == nullptr)
		return true;
	pair<int,char> p = q -> key;
	if (p.first >= left_key or p.first < right_key)
		return false;
	return isBST(q -> left,p.first,right_key) and isBST(q -> right,left_key,p.first);
} */

bool isBinST(Node* q) {
	stack<Node*> S;
	Node* prev = nullptr;
	
	while (!S.empty() or q != nullptr) {
		while (q != nullptr) {
			S.push(q);
			q = q -> left;
		}
		q = S.top();
		S.pop();
		pair<int,char> p = q -> key;
		pair<int,char> pp;
		if (prev != nullptr)
			pp = prev -> key;
		if (prev != nullptr and p.first <= pp.first)
			return false;
		
		prev = q;
		q = q -> right;
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
				Vv.push_back(In_vertex(m,0,'L'));
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
		Vn.push_back(Node(make_pair(Vv[i].m,Vv[i].c)));
		
	fin.close();
	ofstream fout("bst.out");
		
	
	for (int i = 1; i < n; i++) {
		if (Vv[i].c == 'L') {
			if (Vn[Vv[i].p - 1].left == nullptr and Vn[Vv[i].p - 1].key > Vn[i].key) {
				Vn[Vv[i].p - 1].left = &Vn[i];
				Vn[i].parent = &Vn[Vv[i].p - 1];
			}
			else {
				fout << "NO";
				return 0;
			}
		}
		else {
			if (Vn[Vv[i].p - 1].right == nullptr and Vn[Vv[i].p - 1].key <= Vn[i].key) {
				Vn[Vv[i].p - 1].right = &Vn[i];
				Vn[i].parent = &Vn[Vv[i].p - 1];
			}
			else {
				fout << "NO";
				return 0;
			}
		}
	}
	
	//vector<pair<int,char>> v;
	
	//inorder(&Vn[0],v);
	//int MIN = -2147483648;
	//int MAX = 2147483647;
	
/* 	if ((&Vn[0])) {
		fout << "YES";
		return 0;
	}
	
	else {
		fout << "NO";
		return 0;
	} */
	
	if (IsBinSearchTree(&Vn[0]) == false) {
		fout << "NO";
		return 0;
	}
	
	else {
		fout << "YES";
		return 0;
	} 
	
/* 	for (int i = 0; i < v.size() - 1; i++) {
		if ((v[i].first >= v[i + 1].first and v[i].second == 'R' and v[i + 1].second == 'L') or (v[i].first > v[i + 1].first and v[i].second == 'L' and v[i + 1].second == 'L') ) {
			fout << "NO";
			return 0;
		}
	}
 */
	
	fout << "YES";
	
	fout.close();
	
	
	
	return 0;
}