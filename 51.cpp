#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void solution(vector<int>* A, int L, int R, int& fine) {
	
	int k = (L + R) / 2;
	solution(A,L,k,fine);
	solution(A + k + 1,L + k + 1,R,fine);
	
	if (L == k) {
		return;
	}
	
	if (L != k) {
		
	}
	
}

bool comparison(int& a, int& b);

void naive_algorithm(vector<int>* A,int N, int& fine) {
	
	cout << "27\n";
	
	int permutations = 0;
	
	while (permutations != N - 1) {
		
		for (int f = 0; f < N - 1; f++) {
			int i = f;
			//cout << "34 P = " << permutations << "\n";
			
			if (A[N - 2][0] == -1 or A[N - 1][0] == 1)
				break;
			
			while(i < N - 1 and A[i][0] == -1) {
				i++;
			}
			
			int j = i + 1;
			
			while(j < N and A[j][0] == -1) {
				j++;
			}
			
			if ( comparison( A[i][A[i].size() - 1], A[j][0] ) ) {
				
				for (int k = 0; k < A[j].size(); k++) {
					A[i].push_back(A[j][k]);
				}
				
				A[j] = vector<int>({-1});
				permutations++;
				fine += j - i;
				
			}
			
			else if ( comparison(A[j][A[j].size() - 1], A[i][0]) ) {
				
				for (int k = 0; k < A[i].size(); k++) {
					A[j].push_back(A[i][k]);
				}
				
				A[i] = vector<int>({-1});
				cout << "66 " << A[i].size() << A[i][0]; 
				permutations++;
				fine += j - i;
		
			}
			
		}
	
	}
	
}

int main() {
	
	int n;
	
	ifstream fin("input.txt");
	fin >> n;
	vector<int>* A = new vector<int>[n];
	int x;
	for (int i = 0; i < n; i++) {
		fin >> x;
		A[i].push_back(x);
	}
	
	fin.close();
	
	int fine = 0;
	
	naive_algorithm(A,n,fine);
	ofstream fout("output.txt");
	fout << fine;
	fout.close();
	return 0;
}

bool comparison(int& a, int& b) {
	return (a - 1 == b);
}