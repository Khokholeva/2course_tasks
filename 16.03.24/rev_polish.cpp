#include <iostream>
#include <cstdlib>
#include <initializer_list>
#include<stack>
#include <sstream>
#include <string>
using namespace std;

int f2() {
	stack <int> vals;
	int d, a, b;
	char x;

	while (cin >> x) {
		if (isdigit(x)) {
			cin.putback(x);
			cin >> d;
			vals.push(d);
		}
		else if (x == '+') {
			a = vals.top();
			vals.pop();
			b = vals.top();
			vals.pop();
			d = a + b;
			vals.push(d);
		}
		else if (x == '-') {
			a = vals.top();
			vals.pop();
			b = vals.top();
			vals.pop();
			d = b - a;
			vals.push(d);
		}
		else if (x == '*') {
			a = vals.top();
			vals.pop();
			b = vals.top();
			vals.pop();
			d = a * b;
			vals.push(d);
		}
		else if (x == '/') {
			a = vals.top();
			vals.pop();
			b = vals.top();
			vals.pop();
			d = b / a;
			vals.push(d);
		}
	}
	d = vals.top();
	return d;
}

void f1() {
	stack <char> oper;
	stack <int> prior;
	int d;
	char x;
	while (cin >> x) {
		if (isdigit(x)) {
			cin.putback(x);
			cin >> d;
			cout << d << " ";
		}
		else if (x == '+') {
			while (!oper.empty() and prior.top() > 0) {
				cout << oper.top() << " ";
				oper.pop();
				prior.pop();
			}
			oper.push(x);
			prior.push(1);
		}
		else if (x == '-') {
			while (!oper.empty() and prior.top() > 0) {
				cout << oper.top() << " ";
				oper.pop();
				prior.pop();
			}
			oper.push(x);
			prior.push(1);
		}
		else if (x == '*') {
			while (!oper.empty() and prior.top() > 1) {
				cout << oper.top() << " ";
				oper.pop();
				prior.pop();
			}
			oper.push(x);
			prior.push(2);
		}
		else if (x == '/') {
			while (!oper.empty() and prior.top() > 1) {
				cout << oper.top() << " ";
				oper.pop();
				prior.pop();
			}
			oper.push(x);
			prior.push(2);
		}
		else if (x == '(') {
			oper.push(x);
			prior.push(0);
		}
		else if (x == ')') {
			while (!oper.empty() and prior.top() > 0) {
				cout << oper.top() << " ";
				oper.pop();
				prior.pop();
			}
			oper.pop();
			prior.pop();
		}
	}
	while (!oper.empty()) {
		cout << oper.top() << " ";
		oper.pop();
		prior.pop();
	}
	cout << endl;
}

int rev_polish(string s) {
	stringstream st_1, st_2;
	st_1 << s;
	stack <char> oper;
	stack <int> prior;
	stack <int> vals;
	int d,a,b;
	char x;
	//достаем из st_1 и кладем в st_2
	while (st_1 >> x) {
		if (isdigit(x)) {
			st_1.putback(x);
			st_1 >> d;
			st_2 << d << " ";
		}
		else if (x == '+') {
			while (!oper.empty() and prior.top() > 0) {
				st_2 << oper.top() << " ";
				oper.pop();
				prior.pop();
			}
			oper.push(x);
			prior.push(1);
		}
		else if (x == '-') {
			while (!oper.empty() and prior.top() > 0) {
				st_2 << oper.top() << " ";
				oper.pop();
				prior.pop();
			}
			oper.push(x);
			prior.push(1);
		}
		else if (x == '*') {
			while (!oper.empty() and prior.top() > 1) {
				st_2 << oper.top() << " ";
				oper.pop();
				prior.pop();
			}
			oper.push(x);
			prior.push(2);
		}
		else if (x == '/') {
			while (!oper.empty() and prior.top() > 1) {
				st_2 << oper.top() << " ";
				oper.pop();
				prior.pop();
			}
			oper.push(x);
			prior.push(2);
		}
		else if (x == '(') {
			oper.push(x);
			prior.push(0);
		}
		else if (x == ')') {
			while (!oper.empty() and prior.top() > 0) {
				st_2 << oper.top() << " ";
				oper.pop();
				prior.pop();
			}
			oper.pop();
			prior.pop();
		}
	}
	while (!oper.empty()) {
		st_2 << oper.top() << " ";
		oper.pop();
		prior.pop();
	}
	//достаем из st_2
	while (st_2 >> x) {
		if (isdigit(x)) {
			st_2.putback(x);
			st_2 >> d;
			vals.push(d);
		}
		else if (x == '+') {
			a = vals.top();
			vals.pop();
			b = vals.top();
			vals.pop();
			d = a + b;
			vals.push(d);
		}
		else if (x == '-') {
			a = vals.top();
			vals.pop();
			b = vals.top();
			vals.pop();
			d = b - a;
			vals.push(d);
		}
		else if (x == '*') {
			a = vals.top();
			vals.pop();
			b = vals.top();
			vals.pop();
			d = a * b;
			vals.push(d);
		}
		else if (x == '/') {
			a = vals.top();
			vals.pop();
			b = vals.top();
			vals.pop();
			d = b / a;
			vals.push(d);
		}
	}
	d = vals.top();
	return d;

}

int main()
{
	setlocale(LC_ALL, "Russian");
	string s = "3 + 4 * 2 / (1 - 5)";
	cout << s << " = " << rev_polish(s);
	return EXIT_SUCCESS;
}
