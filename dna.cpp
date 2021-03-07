#include <iostream>
#include <vector>
#include <string>

using namespace std;

class DNA_SEQ {
	
	public:
	
	int n;
	//vector<int> seq_id;
	vector<vector<pair<int,int>>> segm;
	char* gene = new char[3*n*10000 + 4];
	DNA_SEQ (int n, /*vector<int> S_ID = vector<int>(),*/ vector<vector<pair<int,int>>> L = vector<vector<pair<int,int>>> ()) : n(n), /*seq_id(S_ID),*/ segm(L) {}
	
};

void make_new_dna_strand(DNA_SEQ& DNA, int& i1, int& i2, int& j1, int& j2);
void new_dna(DNA_SEQ& DNA, int& i1, int& i2, int& j1, int& j2) {
	//cout << i1 << ' ' << i2 << ' ' << j1 << ' ' << j2 << endl;
	make_new_dna_strand(DNA,i1,i2,j1,j2);
	j2--;
	j1++;
	make_new_dna_strand(DNA,i2,i1,j2,j1);
	return;
}

void replace_nucl(DNA_SEQ& DNA, int& i, int& j, char& c) {
	int S = 0;
	for (int u = 0; u < DNA.segm[i].size(); u++) {
		S += DNA.segm[i][u].second - DNA.segm[i][u].first + 1;
		if (j <= S) {
			for (int w = DNA.segm)
			break;
		}
	}
}
	
int main() {
	
	int n;
	cin >> n;

	DNA_SEQ DNA(n);
	DNA.gene[3*n*10000 - 1 + 1] = 'A';
	DNA.gene[3*n*10000 - 1 + 2] = 'C';
	DNA.gene[3*n*10000 - 1 + 3] = 'G';
	DNA.gene[3*n*10000 - 1 + 4] = 'T';
	string input_dna_seq;
	
	for (int i = 0; i < n; i++) {
		cin >> input_dna_seq;
		//DNA.seq_id.push_back(i);
		
		DNA.segm.push_back(vector<pair<int,int>>());
		
		if (i == 0) {
			DNA.segm[i].push_back(make_pair(0,input_dna_seq.length() - 1));
		}
		
		else {
			DNA.segm[i].push_back(make_pair(DNA.segm[i - 1][0].second + 1,DNA.segm[i - 1][0].second + input_dna_seq.length()));
		}
		
		for (int j = DNA.segm[i][0].first; j <= DNA.segm[i][0].second; j++) {
			DNA.gene[j] = input_dna_seq[j - DNA.segm[i][0].first];
		}
	}
	
	//Requests
	int req_num;
	cin >> req_num;
	char req_type;
	
	for (int i = 0; i < req_num; i++) {
		cin >> req_type;
		
		if (req_type == 'X') {
			int i1, i2, j1, j2;
			cin >> i1 >> i2 >> j1 >> j2;
			new_dna(DNA,i1,i2,j1,j2);
		}
		
		else if (req_type[0] == '=') {
			int i,j;
			char c;
			cin >> i >> j >> c;
			
		}
		
		else if (input_dna_seq[0] == '?') {
			
		}
	}
	
	
	return 0;
}

void make_new_dna_strand(DNA_SEQ& DNA, int& i1, int& i2, int& j1, int& j2) {
	DNA.n++;
	int S = 0;
	for (int u = 0; u < DNA.segm[i1 - 1].size(); u++) {
		S += DNA.segm[i1 - 1][u].second - DNA.segm[i1 - 1][u].first + 1;
		if (j1 - 1 <= S) {
			DNA.segm.push_back(vector<pair<int,int>>());
			for (int w = 0; w <= u; w++) {
				if (w < u) {
					DNA.segm[DNA.n - 1].push_back(make_pair(DNA.segm[i1 - 1][w].first,DNA.segm[i1 - 1][w].second));
				}
				else {
					DNA.segm[DNA.n - 1].push_back(make_pair(DNA.segm[i1 - 1][w].first,DNA.segm[i1 - 1][w].first + j1 - 1));
				}
			}
			break;
		}
	}
	
	S = 0;
	
	for (int u = 0; u < DNA.segm[i2 - 1].size(); u++) {
		S += DNA.segm[i2 - 1][u].second - DNA.segm[i2 - 1][u].first + 1;
		if (j2 <= S) {
			DNA.segm.push_back(vector<pair<int,int>>());
			for (int w = u; w < DNA.segm[i2 - 1].size(); w++) {
				if (w > u) {
					DNA.segm[DNA.n - 1].push_back(make_pair(DNA.segm[i2 - 1][w].first,DNA.segm[i2 - 1][w].second));
				}
				else {
					DNA.segm[DNA.n - 1].push_back(make_pair(DNA.segm[i2 - 1][w].first + j2,DNA.segm[i2 - 1][w].second));
				}
			}
			break;
		}
	}
	
	
	for (int i = 0; i < DNA.segm[DNA.n - 1].size(); i++) {
		for (int j = DNA.segm[DNA.n - 1][i].first; j <= DNA.segm[DNA.n - 1][i].second; j++) {
			cout << DNA.gene[j];
		}
	}
	cout << endl;
}