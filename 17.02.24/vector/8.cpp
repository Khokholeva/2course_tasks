#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

bool subseq(vector<double> v, vector<double> sub) {
	vector<double>::iterator i = v.begin();
	for (double x : sub) {
		i = find(i, v.end(), x);
		if (i != v.end()) i++;
		else return false;
	}
	return true;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	vector < double > a{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	vector < double> b{ 3, 5, 7, 8 };
	vector < double> c{ 5,3,7,8 };
	bool ans;
	ans = subseq(a, b);
	cout << ans << endl;
	ans = subseq(a, c);
	cout << ans << endl;

	return EXIT_SUCCESS;
}
