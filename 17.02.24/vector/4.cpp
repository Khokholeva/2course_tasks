#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

vector<double> concat(vector<double> a, vector<double> b) {
	vector<double> res(a.size() + b.size());
	copy(a.begin(), a.end(), res.begin());
	copy(b.begin(), b.end(), res.begin() + a.size());
	return res;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	vector<double> a{ 1, 3,5,7,9 };
	vector<double> b{2, 4, 6, 8 };
	vector<double> c;
	c = concat(a, b);
	for (double x : c) {
		cout << x << " ";
	}
	cout << endl << endl;
	return EXIT_SUCCESS;
}
