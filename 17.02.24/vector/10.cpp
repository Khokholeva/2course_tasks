#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;


void close_search(vector<double> v, double x, int& i, int& j) {
	vector<double>::iterator a;
	a = lower_bound(v.begin(), v.end(), x);
	if (a == v.end()) {
		i = a - v.begin() - 1;
		j = -1;
	}
	else if (*a == x) {
		i = a - v.begin();
		j = i;
	}
	else {
		i = a - v.begin() - 1;
		j = i + 1;
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");
	//10
	// -1 означает граница либо раньше 0 элемента либо позже последнего
	vector<double> u{ 1.25, 4.31, 7.34, 10.5, 15.8, 19.21, 23.5 };
	int i, j;
	close_search(u, 12.6, i, j);
	cout << i << " " << j << endl;
	close_search(u, 7.34, i, j);
	cout << i << " " << j << endl;
	close_search(u, 30, i, j);
	cout << i << " " << j << endl;
	close_search(u, 0.3, i, j);
	cout << i << " " << j << endl;
	cout << endl;
	return EXIT_SUCCESS;
}
