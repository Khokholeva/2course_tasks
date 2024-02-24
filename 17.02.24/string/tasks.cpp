#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

//task 1
bool valid_ip(string s) {
	int dot, prev = 0;
	string a;
	string test = "1234567890";
	int n;
	for (int i = 0; i < 3; i++) {
		dot = s.find_first_of(".", prev);
		if (dot == -1) return false;
		a = s.substr(prev, dot - prev);
		if (a.size() > 3) return false;
		for (int i = 0; i < a.size(); i++) {
			if (test.find_first_of(a[i]) == -1) return false;
		}
		n = stoi(a);
		if (n < 0 or n > 255) return false;
		prev = dot + 1;
	}
	a = s.substr(prev, dot - prev);
	if (a.size() > 3) return false;
	for (int i = 0; i < a.size(); i++) {
		if (test.find_first_of(a[i]) == -1) return false;
	}
	n = stoi(a);
	if (n < 0 or n > 255) return false;
	return true;
}

//task 2
string bracket(string base, string pattern) {
	int n = pattern.size();
	int ind = 0;
	ind = base.find(pattern, ind);
	while (ind != -1) {
		base.insert(ind, "(");
		base.insert(ind + n + 1, ")");
		ind += n + 2;
		ind = base.find(pattern, ind);
	}
	return base;

}

//task 3

int main()
{
	setlocale(LC_ALL, "Russian");
	return EXIT_SUCCESS;
}
