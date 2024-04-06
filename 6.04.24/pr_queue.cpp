#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

struct PrQueue {
	int max_size, size;
	int* values, * priors;
	PrQueue(int s = 10) : max_size(s), values(new int[s]), priors(new int[s]), size(0){}
	~PrQueue() {
		delete[] values;
		delete[] priors;
	}
	bool empty() {
		return size == 0;
	}
	void push(int d, int p) {
		if (size == max_size) {
			cout << "Error: max_size reached" << endl;
			return;
		}
		values[size] = d;
		priors[size] = p;
		int i = size;
		size ++;
		int k;
		while (i > 0 and priors[i] > priors[(i - 1) / 2]) {
			k = values[i];
			values[i] = values[(i - 1) / 2];
			values[(i - 1) / 2] = k;
			k = priors[i];
			priors[i] = priors[(i - 1) / 2];
			priors[(i - 1) / 2] = k;
			i = (i - 1) / 2;
		}
	}
	int pop() {
		if (size == 0) {
			cout << "Error: empty queue" << endl;
			return 0;
		}
		int ans = values[0];
		size --;
		values[0] = values[size];
		priors[0] = priors[size];
		int i = 0, j = 0;
		int k;
		while (i < size) {
			if (i * 2 + 1 < size and priors[j] < priors[i * 2 + 1]) {
				j = i * 2 + 1;
			}
			if (i * 2 + 2 < size and priors[j] < priors[i * 2 + 2]) {
				j = i * 2 + 2;
			}
			if (i == j) break;
			k = values[i];
			values[i] = values[j];
			values[j] = k;
			k = priors[i];
			priors[i] = priors[j];
			priors[j] = k;
			i = j;
		}
		return ans;
	}

};

int main()
{
	setlocale(LC_ALL, "Russian");
	srand((unsigned)time(0));
	PrQueue q;
	int p;
	for (int i = 1; i < 11; i++) {
		p = rand() % 100;
		q.push(i,p);
		for (int j = 0; j < i; j++) {
			cout << q.values[j] << "(" << q.priors[j] << ") ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 1; i < 11; i++) {
		cout << q.pop() << endl;
	}
	return EXIT_SUCCESS;
}
