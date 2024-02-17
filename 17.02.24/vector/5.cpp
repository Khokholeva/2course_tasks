#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

vector<double> repeat(vector<double> v, int n) {
	int s = v.size();
	vector<double> res(s * n);
	for (int i = 0; i < n; i++) {
		copy(v.begin(), v.end(), res.begin() + s*i);
	}
	return res;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	vector<double> d{ 1,2,3 };
	vector<double> e;
	e = repeat(d, 5);
	for (double x : e) {
		cout << x << " ";
	}
	return EXIT_SUCCESS;
}
