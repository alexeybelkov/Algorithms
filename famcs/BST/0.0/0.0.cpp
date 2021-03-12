#include <iostream>
#include <fstream>

int main() {
	std:: ifstream fin("input.txt");
	
	long long x = 0;
	long long S = 0;
	
	while (!fin.eof()) {
		fin >> x;
		S += x;
	}
	
	S -= x;
	
	fin.close();
	
	std:: ofstream fout("output.txt");
	
	fout << (long long) S;
	
	fout.close();
	
	return 0;
	
}