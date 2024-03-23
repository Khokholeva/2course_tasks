#include <iostream>
#include <cstdlib>
#include<stack>
using namespace std;

struct Node {
	double d;
	Node* n;
};

struct Queue {
	Node *head, * tail;
	Queue(): head(nullptr), tail(nullptr) {}
	~Queue() {
		Node* p, * q;
		p = head;
		while (p != nullptr) {
			q = p->n;
			delete p;
			p = q;
		}
	}
	bool empty() {
		return (head == nullptr);
	}
	void push(double d) {
		Node* p = new Node;
		p->d = d;
		p->n = nullptr;
		if (head == nullptr) head = p;
		else tail->n = p;
		tail = p;
	}
	double pop() {
		if (head == nullptr) {
			cout << "Error: empty queue" << endl;
			return 0;
		}
		Node* del = head;
		double res = del->d;
		head = del->n;
		if (head == nullptr) tail = nullptr;
		delete del;
		return res;
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
