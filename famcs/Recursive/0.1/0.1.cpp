//Порядок перемножения матриц
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int solution(int** A, int n) {
	
	int** F = new int*[n];
	
	for (int i = 0; i < n; i++) {
		F[i] = new int[n];
		F[i][i] = 0;
	}
	
	for (int q = 0; q < n; q++) {
		for (int i = 0; i < n - q - 1; i++) {
			int M = INT_MAX;
			for (int k = i; k < i + q + 1; k++) {
				if (F[i][k] + F[k + 1][i + 1 + q] + A[i][0]*A[k][1]*A[i + q + 1][1] < M) {
					M = F[i][k] + F[k + 1][i + 1 + q] + A[i][0]*A[k][1]*A[i + q + 1][1];
				}
			}
			F[i][i + q + 1] = M;
		}
	}
	
	return F[0][n - 1];
}
	
int main() {
	int n;
	ifstream fin("input.txt");
	fin >> n;
	int** A = new int*[n];
	
	for (int i = 0; i < n; i++) {
		A[i] = new int[2];
		fin >> A[i][0];
		fin >> A[i][1];
	}
	
	fin.close();
	
	ofstream fout("output.txt");
	auto s = solution(A,n);
	fout << s;
	cout << s;
	fout.close();
}