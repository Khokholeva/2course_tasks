#include <iostream>
#include <cstdlib>
#include<stack>
using namespace std;

struct Queue {
	stack<double> inp, out;
	Queue() = default;
	~Queue() = default;
	bool empty() {
		return inp.empty() and out.empty();
	}
	void push(double d) {
		inp.push(d);
	}
	double pop() {
		if (inp.empty() and out.empty()) {
			cout << "Error: empty queue" << endl;
			return 0;
		}
		double d;
		if (out.empty()) {
			while (!inp.empty()) {
				d = inp.top();
				inp.pop();
				out.push(d);
			}
		}
		d = out.top();
		out.pop();
		return d;
	}
}; 

int main()
{
	setlocale(LC_ALL, "Russian");
	Queue q(10);
	q.push(1);
	q.push(3);
	q.push(5);
	q.push(7);
	cout << q.pop() << " ";
	cout << q.pop() << " ";
	cout << q.pop() << " "; 
	cout << q.pop() << " ";
	cout << q.pop() << endl;
	return EXIT_SUCCESS;
}
