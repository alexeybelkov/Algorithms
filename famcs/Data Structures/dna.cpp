#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>


// 2 1 1 0
// 3 0 1 1
// 2 0 1 2

using namespace std;

class DNA_SEQ {
	public:
	int n;
	int gene_length = 3*n*10000  + 4;
	vector<vector<pair<int,int>>> segm;
	char* gene = new char[3*n*10000 + 4];
	DNA_SEQ (int n, vector<vector<pair<int,int>>> L = vector<vector<pair<int,int>>> ()) : n(n), segm(L) {}
};

void make_new_dna_strand(DNA_SEQ& DNA, int& i1, int& i2, int& j1, int& j2);
void new_dna(DNA_SEQ& DNA, int& i1, int& i2, int& j1, int& j2) {
	make_new_dna_strand(DNA,i1,i2,j1,j2);
	make_new_dna_strand(DNA,i2,i1,j2,j1);
}

void replace_nucl(DNA_SEQ& DNA, int& i, int& j, char& c) {
	i--;
	j--;
	int S = 0;
	
	for (int u = 0; u < DNA.segm[i].size(); u++) {
		S += DNA.segm[i][u].second - DNA.segm[i][u].first + 1;
		if (j + 1 <= S) {
			j -= S - (DNA.segm[i][u].second - DNA.segm[i][u].first + 1);
			int temp = DNA.segm[i][u].second;
			DNA.segm[i][u].second = DNA.segm[i][u].first + j - 1;
			int nucl_index;
			for (int v = DNA.gene_length - 1; v >= DNA.gene_length - 1 - 3; v--) {
				if (c == DNA.gene[v]) {
					nucl_index = v;
					break;
				}
			}
			auto it = DNA.segm[i].cbegin();
			pair<int,int> temp_pair = make_pair(nucl_index,nucl_index);
			DNA.segm[i].insert(it + u + 1,temp_pair);
			
			if (DNA.segm[i][u].first + j + 1 <= temp) {
				it = DNA.segm[i].cbegin();
				temp_pair = make_pair(DNA.segm[i][u].first + j + 1,temp);
				DNA.segm[i].insert(it + u + 2,temp_pair);
			}
			
			break;
		}
	}
	
	for (int p = 0; p < DNA.segm[i].size(); p++) {
		cout << '>';
		for (int k = DNA.segm[i][p].first; k <= DNA.segm[i][p].second; k++) {
			cout << DNA.gene[k];
		}
		cout << '<';
		cout << " {" << DNA.segm[i][p].first << ' ' << DNA.segm[i][p].second << "} ";
	}
	cout << endl;
	
}

void count_nucleo(DNA_SEQ& DNA, int& i, int& j1, int& j2) {
	i--;
	j1--;
	j2--;
	unordered_map<char,int> M;
	M['A'] = 0;
	M['C'] = 0;
	M['G'] = 0;
	M['T'] = 0;
	
	int S = 0;
	
	for (int u = 0; u < DNA.segm[i].size(); u++) {
		S += DNA.segm[i][u].second - DNA.segm[i][u].first + 1;
		if (j1 + 1 <= S) {
			j1 -= S - (DNA.segm[i][u].second - DNA.segm[i][u].first + 1);
			S -= DNA.segm[i][u].second - DNA.segm[i][u].first + 1;
			for (int v = u; v < DNA.segm[i].size(); v++) {
				S += DNA.segm[i][v].second - DNA.segm[i][v].first + 1;
				if (j2 + 1 <= S) {
					j2 -= S - (DNA.segm[i][v].second - DNA.segm[i][v].first + 1);
					if (v == u) {
						for (int q = DNA.segm[i][v].first + j1; q <= DNA.segm[i][v].first + j2; q++) {
							M[DNA.gene[q]] += 1;
						}
					}
					else {
						for (int q = DNA.segm[i][v].first; q <= DNA.segm[i][v].first + j2; q++) {
							M[DNA.gene[q]] += 1;
						}
					}
					break;
				}
				else {
					if (v == u) {
						for (int q = DNA.segm[i][v].first + j1; q <= DNA.segm[i][v].second; q++) {
							M[DNA.gene[q]] += 1;
						}
					}
					
					else {
						for (int q = DNA.segm[i][v].first; q <= DNA.segm[i][v].second; q++) {
							M[DNA.gene[q]] += 1;
						}
					}
				}
			}
			break;
		}
	}
	
	cout << "____________\n";
	cout << M['A'] << ' ' << M['C'] << ' ' <<  M['G'] << ' ' << M['T'] << "    |\n";
	cout << "------------\n";
	
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
		
		else if (req_type == '=') {
			int i,j;
			char c;
			cin >> i >> j >> c;
			replace_nucl(DNA,i,j,c);
		}
		
		else if (req_type == '?') {
			int i,j1,j2;
			cin >> i >> j1 >> j2;
			count_nucleo(DNA,i,j1,j2);
		}
	}
	
	
	return 0;
}

void make_new_dna_strand(DNA_SEQ& DNA, int& i1, int& i2, int& j1, int& j2) {
	DNA.n++;
	int S = 0;
	int j11 = j1;
	if (j1 > 0) {
		for (int u = 0; u < DNA.segm[i1 - 1].size(); u++) {
			S += DNA.segm[i1 - 1][u].second - DNA.segm[i1 - 1][u].first + 1;
			if (j1 <= S) {
				j1 -= S - (DNA.segm[i1 - 1][u].second - DNA.segm[i1 - 1][u].first + 1);
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
	}
	
	for (int k = 0; k < DNA.segm[i2 - 1].size(); k++) {
		S += DNA.segm[i2 - 1][k].second - DNA.segm[i2 - 1][k].first + 1;
	} 
	
	if (j2 <= S) {
		if (j11 <= 0) {
			DNA.segm.push_back(vector<pair<int,int>>());
		}
		S = 0;
		for (int u = 0; u < DNA.segm[i2 - 1].size(); u++) {
			S += DNA.segm[i2 - 1][u].second - DNA.segm[i2 - 1][u].first + 1;
			if (j2 + 1 <= S) {
				j2 -= S - (DNA.segm[i2 - 1][u].second - DNA.segm[i2 - 1][u].first + 1);
				//DNA.segm.push_back(vector<pair<int,int>>());
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
	}
	
	if (j11 <= 0 and j2 >= S) {
		DNA.n--;
	}
	
	for (int i = 0; i < DNA.segm[DNA.n - 1].size(); i++) {
		cout << '>';
		for (int j = DNA.segm[DNA.n - 1][i].first; j <= DNA.segm[DNA.n - 1][i].second; j++) {
			cout << DNA.gene[j]; /*<< " {" << DNA.segm[DNA.n - 1][i].first << ' ' << DNA.segm[DNA.n - 1][i].second << "} ";*/
		}
		cout << '<';
		cout << " {" <<DNA.segm[DNA.n - 1][i].first << ' ' << DNA.segm[DNA.n - 1][i].second << "} ";
	}
	 cout << "  :X" << endl;
}