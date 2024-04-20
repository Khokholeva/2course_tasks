#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

int digit(int x, int n) {
	return (x >> n) & 1;
}

template <class D>
struct DSNode {
	int key;
	D data;
	DSNode * zero, * one;
	DSNode(int k, D d = 0, DSNode* z = nullptr, DSNode* o = nullptr): key(k), data(d), zero(z), one(o) {}
};

template <class D>
void f_del(DSNode<D>*& p)
{
	if (p == nullptr)
		return;
	f_del(p->one);
	f_del(p->zero);
	delete p;
	p = nullptr;
}

template <class D>
void f_print(DSNode<D>* r, int d = 0)
{
	if (r == nullptr) return;
	f_print(r->one, d + 3);
	for (int i = 0; i < d; i++)
		cout << ' ';
	cout << r->key << ": " << r->data << endl;
	f_print(r->zero, d + 3);
}


template <class D> 
DSNode<D>* f_search(DSNode<D>* r, int k, int level) {
	if (r == nullptr) return nullptr;
	if (r->key == k) return r;
	if (digit(k, level) == 0) return f_search(r->zero, k, level + 1);
	return f_search(r->one, k, level+1);
}

template <class D>
void f_insert(DSNode<D>*& r, int k, D d, int level) {
	if (r == nullptr) {
		r = new DSNode<D>(k, d);
		return;
	}
	if (r->key == k) {
		cout << "Error: key already exists" << endl;
		return;
	}
	if (digit(k, level) == 0) {
		f_insert(r->zero, k, d, level + 1);
	}
	else f_insert(r->one, k, d, level +1);
}

template <class D>
void f_delete(DSNode<D>*& r, int k, int level) {
	if (r == nullptr) return;
	if (r->key == k) {
		DSNode<D>* prev = nullptr;
		DSNode<D>* n = r;
		while (n->zero != nullptr or n->one !=nullptr) {
			prev = n;
			if (n->zero != nullptr) n = n->zero;
			else n = n->one;
		}
		
		if (prev != nullptr) {
			r->key = n->key;
			r->data = n->data;
			if (n == prev->zero) prev->zero = nullptr;
			else prev->one = nullptr;
		}
		delete n;
		return;
	}
	if (digit(k, level) == 0) return f_delete(r->zero, k, level+1);
	return f_delete(r->one, k, level+1);
}

template <class D>
struct DSTree {
	DSNode<D>* root;
	DSTree(DSNode<D>* r): root(r) {}
	DSTree(): root(nullptr) {}
	~DSTree() {
		f_del(root);
	}
	void print() {
		f_print(root);
	}
	DSNode<D>* search(int key) {
		return f_search(root, key, 0);
	}
	void insert(int k, D d) {
		f_insert(root, k, d, 0);
	}
	void del(int k) {
		f_delete(root, k, 0);
	}
};

template <class D>
void table_print(DSNode<D>* r, int w1 = 5, int w2 = 5) {
	if (r == nullptr) return;
	cout << setw(w1) << r->key << setw(w2) << r->data << endl;
	table_print(r->zero, w1, w2);
	table_print(r->one, w1, w2);
}

void count_numbers() {
	string name;
	cin >> name;
	ifstream source(name);
	DSTree<int> tree;
	DSNode<int>* n;
	int x;
	int key_max = 0, num_max = 0;
	while (source >> x) {
		key_max = (key_max < x) ? x : key_max;
		n = tree.search(x);
		if (n == nullptr) tree.insert(x, 1);
		else 
		{
			n->data += 1; 
			num_max = (num_max < n->data) ? n->data : num_max;
		}
		
	}
	int w1 = 1, w2 = 4;
	key_max /= 10;
	num_max /= 10;
	while (key_max > 0) {
		w1 += 1;
		key_max /= 10;
	}
	while (num_max > 0) {
		w2 += 1;
		num_max /= 10;
	}
	table_print(tree.root, w1, w2);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	count_numbers();
	return EXIT_SUCCESS;
}
