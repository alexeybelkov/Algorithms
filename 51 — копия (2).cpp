#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void Fine(int* S, int n,int& fine, int N) {
	
	if (n == N) {
		//fine -= abs(S[n] - S[n - 1]);
	}
	
	else if (n == 1) {
		fine -= abs(S[1] - S[2]);
	}
	
	else if (n >= 2 and n < N) {
		fine -= min(abs(S[n] - S[n - 1]),abs(S[n] - S[n + 1]));
	}
	
	else return;
	
	Fine(S,n - 1,fine,N);
	
}

int main() {
	
	int n;
	
	ifstream fin("input.txt");
	fin >> n;
	
	int* S = new int[n + 1];
	S[0] = -n;
	for (int i = 1; i <= n; i++) {
		int x;
		fin >> x;
		S[x] = i;
	}
	
	fin.close();
	
	int fine = n*n;
	Fine(S,n,fine,n);
	cout << endl << n*n - fine << endl << "fine = " << fine << endl; ;
	ofstream fout("output.txt");
	fout << n*n - fine;
	fout.close();
	return 0;
}