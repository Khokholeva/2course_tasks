#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

vector<double>::iterator second_occur(vector<double> &v, double x) {
	vector<double>::iterator i;
	i = find(v.begin(), v.end(), x);
	if (i != v.end()) i = find(i+1, v.end(), x);
	return i
}

int main()
{
	setlocale(LC_ALL, "Russian");
	vector <double> f{ 3, 2, 5, 9, 4, 5, 7 };
	vector<double>::iterator i;
	double test[] = {1, 5, 9};
	for (double x : test) {
		i = second_occur(f, x);
		if (i != f.end()) cout << *i << endl;
		else cout << "No second occurance of " << x << endl;
	}
	return EXIT_SUCCESS;
}
