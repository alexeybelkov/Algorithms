#include <iostream>
#define long long ll

bool binary_search(int* A,int x,int n) {
	int L = 0;
	int R = n;
	int k = 0;
	
	while (L < R) {
		
		k = (L + R) / 2;
		
		if (x == A[k]) {
			return true;
		}
		
		else if (x < A[k]) {
			R = k;
		}
		
		else {
			L = k + 1;
		}
		
	}
	
	return false;
}

int lower_bound(int* A, int x, int n) {
	int L = 0;
	int R = n;
	int k = 0;
	
	while (L < R) {
		k = (L + R) / 2;
		if (x <= A[k]) {
			R = k;
		}
		else {
			L = k + 1;
		}	
	}
	
	return L;
}

int upper_bound(int* A, int x, int n) {
	int L = 0;
	int R = n;
	int k = 0;
	
	while (L < R) {
		k = (L + R) / 2;
		if (x < A[k]) {
			R = k;
		}
		else {
			L = k + 1;
		}
	}
	return L;
}

int main() {
	
	int n;
	std::cin >> n;
	int* A = new int[n];
	
	for (int i = 0; i < n; i++) {
		std::cin >> A[i];
	}
	
	int k;
	std::cin >> k;
	
	//int* requests = new int[k];
	int request;
	
	for (int i = 0; i < k; i++) {
		std::cin >> request;
		std::cout << binary_search(A,request,n) << ' ' << lower_bound(A,request,n) << ' ' << upper_bound(A,request,n) << '\n';
	}
	
	return 0;
}
