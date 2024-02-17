#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

void enlarge(vector<double>& v) {
	vector<double>::iterator i;
	i = v.begin();
	double t;
	t = *i;
	i++;
	while (i != v.end()) {
		t += *i;
		t /= 2;
		i = v.insert(i, t);
		i++;
		t = *i;
		i++;
	}
}
int main()
{
	setlocale(LC_ALL, "Russian"); //для вывода русских букв
	vector<double> v{ 1,2,7,10,5 };
	enlarge(v);
	for (double x : v) {
		cout << x << " ";
	}
	return EXIT_SUCCESS;
}
