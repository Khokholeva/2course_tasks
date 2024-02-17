#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

int last_occ_sort(vector<double>& v, double x) {
	vector<double>::iterator i;
	i = upper_bound(v.begin(), v.end(), x);
	i -= 1;
	if (*i == x) return i - v.begin();
	else return -1;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	vector<double> v{ 1, 2, 2, 4, 4, 4, 6, 7 };
	int i, j;
	i = last_occ_sort(v, 4);
	cout << i << endl;
	i = last_occ_sort(v, 3);
	cout << i << endl;
	return EXIT_SUCCESS;
}
