#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//task 1
bool valid_ip(string s) {
	int dot, prev = 0;
	string a;
	int n;
	for (int i = 0; i < 3; i++) {
		dot = s.find_first_of(".", prev);
		if (dot - prev > 3 or dot - prev < 1) return false;
		a = s.substr(prev, dot - prev);
		for (int i = 0; i < a.size(); i++) {
			if (not isdigit(a[i])) return false;
		}
		n = stoi(a);
		if (n < 0 or n > 255) return false;
		prev = dot + 1;
	}
	a = s.substr(prev);
	if (a.size() < 1 or a.size() > 3) return false;
	for (int i = 0; i < a.size(); i++) {
		if (not isdigit(a[i])) return false;
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
string edit_sums(string base) {
	int l = 0, r = 0, summ = 0, n = 0;
	string ans, a;
	int s = base.size();
	for (int i = 0; i < s; i++) {
		if (isdigit(base[i])) {
			r++;
		}
		else if (base[i] == '+' and i != 0 and i != s-1 and isdigit(base[i-1]) and isdigit(base[i+1])) {
			a = base.substr(l, r - l);
			n = stoi(a);
			summ += n;
			r++;
			l = r;
			
		}
		else {
			if (r > l) {
				a = base.substr(l, r - l);
				n = stoi(a);
				summ += n;
				ans += to_string(summ);
				summ = 0;
			}
			ans += base[i];
			r++;
			l = r;
		}
	}
	if (r > l) {
		a = base.substr(l, r - l);
		n = stoi(a);
		summ += n;
		ans += to_string(summ);
	}
	return ans;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	return EXIT_SUCCESS;
}
