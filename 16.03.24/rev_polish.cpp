#include <iostream>
#include <cstdlib>
#include <initializer_list>
#include<stack>
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
			d = a - b;
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
			d = a / b;
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
int main()
{
	setlocale(LC_ALL, "Russian");
	return EXIT_SUCCESS;
}
