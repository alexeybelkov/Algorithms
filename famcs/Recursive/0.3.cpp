#include <iostream>
#include <algorithm>

using namespace std;

auto d = 1000000000 + 7;

int solution(int** F, int n, int k) {
	
	return F[n][k];
}

int main() {
	int n,k;
	cin >> n >> k;
	
	int p = 0;
	
	if (n > 1000) {
		int N = n;
		while (N > 1000) {
			N -= 1000;
			p++;
		}
	}
	
	int q = 0;
	
	if (k > 1000) {
		int K = k;
		while (K > 1000) {
			K -= 1000;
			q++;
		}
	}
	
	
	
	int** F = new int*[n + 1];
	for (int i = 0; i < n + 1; i++) {
		if (i < k + 1) {
			F[i] = new int[i + 1];
			F[i][i] = 1;
		}
		else {
			F[i] = new int[k + 1];
		}
		F[i][0] = 1;
	}
	
	cout << C(n,k);
	
	return 0;
}