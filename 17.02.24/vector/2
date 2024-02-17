#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

void del(vector<double>& v) {
	vector <double > ::iterator i;
	i = v.begin();
	while (i != v.end()) {
		i = v.erase(i);
		if (i != v.end()) i++;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	vector<double> v{ 1,2,7,10,5 };
	del(v);
	for (double x : v) {
		cout << x << " ";
	}
	return EXIT_SUCCESS;
}
