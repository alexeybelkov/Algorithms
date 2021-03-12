#include <iostream>

using namespace std;

auto d = 1000000000 + 7;

int solution(int** F, int n, int k) {
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j < i; j++) {
			F[i][j] = (F[i - 1][j - 1] % d + F[i - 1][j] % d) % d;
			if (i == n and j == k) {
				break;
			}
		}
	}
	
	return F[n][k];
}

int main() {
	int n,k;
	cin >> n >> k;
	
	int** F = new int*[n + 1];
	for (int i = 0; i < n + 1; i++) {
		F[i] = new int[n + 1];
		F[i][i] = 1;
		F[i][0] = 1;
	}
	
	cout << solution(F,n,k);
	
	return 0;
}