#include <iostream>
#include <cstdlib>
#include <initializer_list>
using namespace std;

struct Stack {
	int head;
	int size;
	double* ar;
	Stack() : ar(new double[10] {}), head(-1), size(10) {}
	Stack(int s) : ar(new double[s] {}), head(-1), size(s) {}
	~Stack() {
		delete[] ar;
	}
	bool is_empty() {
		return head == -1;
	}
	void push(double x) {
		if (head == size - 1) {
			cout << "Error: full stack";
			return;
		}
		head += 1;
		ar[head] = x;
	}
	double pop() {
		double res;
		if (head > -1) {
			res = ar[head];
			ar[head] = 0;
			head -= 1;
			return res;
		}
		cout << "Error: empty stack" << endl;
		return 0;
	}
};
int main()
{
	setlocale(LC_ALL, "Russian");
	Stack s;
	cout << boolalpha << s.is_empty() << endl;
	s.push(1);
	s.push(2);
	s.push(3);
	cout << boolalpha << s.is_empty() << endl;
	double x;
	x = s.pop();
	cout << x << endl;
	x = s.pop();
	cout << x << endl;
	x = s.pop();
	cout << x << endl;
	x = s.pop();
	cout << x << endl;
	return EXIT_SUCCESS;
}
