#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void make_swap(int* S, int a, int b) {
	
	if (a < 0) {
		return;
	}
	
	else if (a == 0 and S[0] == S[1]) {
		S[0] = S[b];
		return;
	}
	
	else if (a > 0) {
		
		if (S[a] == S[a - 1]) {
			make_swap(S,a - 1,b);
			S[a] = S[b];
			//S[a - 1] = S[b];
			return;
		}
		
		else {
			return;
		}
		
	}
	
}

void solution(int* S, int n, int& fine) {
	
	if (n <= 2) {
		fine = 3 % n;
		return;
	}
	
	int min = n;
	int a;
	int b;
	
	for (int K = 0; K < n; K++) {
	
		for (int i = 0; i < n; i++) {
			
			if (i == 0) {
				if (abs(S[i] - S[i + 1]) < min and abs(S[i] - S[i + 1]) > 0) {
					min = abs(S[i] - S[i + 1]);
					a = i;
					b = i + 1;
				}
			}
			
			else if (i == n - 1) {
				if (abs(S[i] - S[i - 1]) < min and abs(S[i] - S[i - 1]) > 0) {
					min = abs(S[i] - S[i - 1]);
					a = i;
					b = i - 1;
				}
			}
			
			//else if ( (abs(S[i] - S[i + 1]) < min and abs(S[i] - S[i + 1]) > 0) or (abs(S[i] - S[i - 1]) < min and abs(S[i] - S[i - 1]) > 0) ) {
			else if ( abs(S[i] - S[i - 1]) == 0 or abs(S[i] - S[i + 1]) == 0) {	
				
				if (0 < abs(S[i] - S[i + 1]) and abs(S[i] - S[i + 1]) < min) {
						a = i;
						b = i + 1;
						min = abs(S[i] - S[i + 1]);
				}
					
				else if (min > abs(S[i] - S[i - 1]) and abs(S[i] - S[i - 1]) > 0) {
						a = i;
						b = i - 1;
						min = abs(S[i] - S[i - 1]);
				}
				
			}

			else {
				if (abs(S[i] - S[i - 1]) < abs(S[i] - S[i + 1]) and abs(S[i] - S[i - 1]) < min) {
						a = i;
						b = i - 1;
						min = abs(S[i] - S[i - 1]);
				}
				
				else if (abs(S[i] - S[i - 1]) >= abs(S[i] - S[i + 1]) and abs(S[i] - S[i + 1]) < min) {
					a = i;
					b = i + 1;
					min = abs(S[i] - S[i + 1]);
				}
			}
			
		}
		
		if (a != b) {
			if (a < b)
				make_swap(S,a,b);
			else if (a > b)
				make_swap(S,b,a);
			fine += min;
			a = 0;
			b = 0;
		}
		min = n;
	}
	for (int i = 0; i < n; i++) {
		cout << S[i] << ' ';
	}
	
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
	
/* 	int** A = new int*[n];
	
	for (int i = 0; i < n; i++) {
		A[i] = new int[n];
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][0] = 0;
			A[0][j] = 0;
			A[i][j] = n + n;
		}
	} */
	
	fin.close();
	
	int fine = 0;
	solution(S,n,fine);
	cout << endl << fine << endl;
	ofstream fout("output.txt");
	fout << fine;
	fout.close();
	return 0;
}