#include <iostream>
#include <vector>
#include <algorithm>

namespace std {

    template <class T>
    ostream& operator << (ostream& os, vector<T>& V) {

        int n = V.size();
        for (int i = 0; i < n; i++) {
            if (n - i >= 2)
                os << V[i] << " ";
            else os << V[i];
        }

        return os;
    }

};

namespace std {
	
	istream& operator >> (istream& is, vector<int>& V) {
		
		for (int i = 0; i < V.size(); i++)
			is >> V[i];
			
		return is;
	}
	
};

long long MaxPairwiseProduct(const std::vector<int>& numbers) {
    long long product = 0;
    int n = numbers.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            product = std::max(product, (long long)numbers[i]*(long long)numbers[j]);
        }
    }   
    return product;
}

long long MaxPairwiseProductFast(const std::vector<int>& numbers) {
   
    int n = numbers.size();
    int max_index1 = -1;
    for (int i = 0; i < n; i++) {
        if (max_index1 == -1 || (numbers[i] > numbers[max_index1]))
            max_index1 = i;
    }

    int max_index2 = (max_index1 + 1)%n;
    for (int i = 0; i < n; i++) {
        //if (max_index1 != max_index2 && max_index2 == -1 || numbers[i] > numbers[max_index2])
        if ((i != max_index1) && numbers[i] >= numbers[max_index2]) {
            max_index2 = i;
		}
    }
    return( (long long) numbers[max_index1]*(long long) numbers[max_index2] );
}

int main() {

	int n;
	std::cin >> n;
	std::vector <int> V(n);
	std::cin >> V;
	std::cout << MaxPairwiseProductFast(V);
	

    return 0;
}