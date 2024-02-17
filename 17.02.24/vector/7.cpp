#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

vector<double>::iterator last_occure(vector<double>& v, double x) {
	vector<double>::iterator i;
	vector<double>::iterator j = v.end();
	i = find(v.begin(), v.end(), x);
	while (i != v.end()) {
		j = i;
		i = find(i + 1, v.end(), x);
	}
	return j;
}

int main()
{
	setlocale(LC_ALL, "Russian");
  vector <double> g{ 3, 2, 5, 9, 4, 5, 7, 1, 5, 8 };
  i = last_occure(g, 5);
  cout << *i << " " << *(i+1);
}
