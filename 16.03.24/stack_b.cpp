#include <iostream>
#include <cstdlib>
#include <initializer_list>
using namespace std;

struct Node {
	double d;
	Node* n;
};

struct Stack {
	Node* ar;
	Stack() : ar(nullptr) {}
	~Stack() {
		Node* p, *q;
		p = ar;
		while (p != nullptr) {
			q = p->n;
			delete p;
			p = q;
		}
	}
	bool is_empty() {
		return ar == nullptr;
	}
	void push(double x) {
		Node *new_val = new Node;
		new_val->d = x;
		new_val->n = ar;
		ar = new_val;
	}
	double pop() {
		if (ar == nullptr) {
			cout << "Error: empty stack" << endl;
			return 0;
		}
		double res;
		Node* p;
		res = ar->d;
		p = ar;
		ar = ar->n;
		delete p;
		return res;
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
