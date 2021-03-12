#include <fstream>
#include <algorithm>

int solution(int* A, int n) {
	
	int* F = new int[n + 1];
	
	F[0] = -2147483648 ;
	F[1] = A[0];
	F[2] = -2147483648;
	
	
	for (int i = 3; i <= n; i++) {
		F[i] = std::max(F[i - 2],F[i - 3]) + A[i - 1];
	}
	
	if (F[n] >= 0 ) {	
		return F[n];
	}
	
	else {
		return -1;
	}
	
}

int main() {
	
	int n;
	
	std::ifstream fin("input.txt"); 
	fin >> n;
	int* A = new int[n];
	
	for (int i = 0; i < n; i++) {
		fin >> A[i];
	}
	
	fin.close();
	
	std::ofstream fout("output.txt");
	fout << solution(A,n);
	fout.close();
	
	return 0;
}