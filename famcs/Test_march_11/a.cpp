#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int main () {
	
	int n;
	ifstream fin("input.txt");
	fin >> n;
	
	int** A = new int*[n];
	
	for (int i = 0; i < n; i++) {
		A[i] = new int[i + 5];
		for (int j = 2; j < i + 3; j++) {
			fin >> A[i][j];
		}
		
		for (int j = 0; j < 2; j++) {
			A[i][j] = INT_MIN;
		}
		
		for (int j = i + 3; j < i + 5; j++) {
			A[i][j] = INT_MIN;
		}
		
	}
	fin.close();
	
	for (int i = 1; i < n; i++) {
		for (int j = 2; j <= i + 2; j++) {
			if (j == 2) {
				A[i][j] = A[i - 1][2] + A[i][j];
			}
			else if (j == i + 2) {
				A[i][j] = A[i - 1][i + 1] + A[i][j];
			}
			else {
				A[i][j] = max(A[i - 1][j - 1],A[i - 1][j]) + A[i][j];
			}
		}
	}
	
	int m = A[n - 1][2];
	int k = 2;
	for (int i = 2; i < n + 2; i++) {
		cout << A[n - 1][i] << ' ';
		if  (A[n - 1][i] > m) {
			k = i;
			m  = A[n - 1][i];
		}
	}
	
	cout << k;
	ofstream fout("output.txt");
	fout << A[n - 1][k];
	return 0;
}