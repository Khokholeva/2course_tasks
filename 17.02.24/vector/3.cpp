#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	vector<double> w{1, 3,5,7,9};
	double u[5];
	copy(w.begin(), w.end(), u);
	for (double x : u) {
		cout << x << " ";
	}
	cout << endl;
	return EXIT_SUCCESS;
}
