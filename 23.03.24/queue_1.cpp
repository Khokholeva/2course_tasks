#include <iostream>
#include <cstdlib>
#include<stack>
using namespace std;

struct Queue {
	double* val;
	int head, size, max_size;

	Queue(): max_size(10), head(0), size(0), val(new double[10] {}) {}
	Queue(int max_s): max_size(max_s), head(0), size(0), val(new double[max_s] {}) {}
	~Queue() {
		delete[] val;
	}
	bool empty() {
		return size == 0;
	}
	void push(double d) {
		if (size == max_size) {
			cout << "Error: size limit reached" << endl;
			return;
		}
		val[(head + size) % max_size] = d;
		size++;
	}
	double pop() {
		if (size == 0) {
			cout << "Error: empty queue" << endl;
			return 0;
		}
		double d = val[head];
		head = (head + 1) % max_size;
		size--;
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
