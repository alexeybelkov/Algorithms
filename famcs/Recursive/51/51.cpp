#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
int correct_solution(int** A, int* S, int n);


int solution(int** A, int* S, int n) {
	
	return 0;
}


int main() {
	
	int n;
	
	ifstream fin("input.txt");
	fin >> n;
	
	int* S = new int[n];
	for (int i = 0; i < n; i++) {
		int x;
		fin >> x;
		S[x - 1] = i;
	}
	
	fin.close();
	
	int** A = new int*[n];
	for (int i = 0; i < n; i++) {
		A[i] = new int[n];
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				A[i][j] = 0;
			}
			else {
				A[i][j] = n*n;
			}
		}
	}

	int fine = solution(A,S,n);
	cout << fine;
	ofstream fout("output.txt");
	fout << fine;
	fout.close();
	return 0;
}





int correct_solution(int** A, int* S, int n) {
	
	for (int i = 0; i < n; i++) {
		for (int j = i; j >= 0; j--) {
			for (int k = j; k < i; k++) {
				A[j][i] = min(A[j][i], A[j][k] + A[k + 1][i] + abs(S[k] - S[i]));
			}
		}
	}
	
	return A[0][n - 1];
}