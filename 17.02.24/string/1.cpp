#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

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

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << valid_ip("192.168.0.1") << endl;
	cout << valid_ip("124.4.225.60") << endl;
	cout << valid_ip("192.168.0") << endl;
	cout << valid_ip("192.168.0.600") << endl;
	cout << valid_ip("192.a10.0.6") << endl;
	cout << valid_ip("192.10.0.1b") << endl;
	return EXIT_SUCCESS;
}
