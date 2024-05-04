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
	f_print(r->one, d + 1);
	for (int i = 0; i < d; i++)
		cout << '\t';
	cout << r->key << ": " << r->data << endl;
	f_print(r->zero, d + 1);
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
	if (r->key == k) return;
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
		else {
			r = nullptr;
		}
		delete n;
		return;
	}
	if (digit(k, level) == 0) return f_delete(r->zero, k, level+1);
	return f_delete(r->one, k, level+1);
}

template <class D>
void f_search_mask1(DSNode<D>* r, int mask, int level) {
	if (r == nullptr) return;
	f_search_mask1(r->one, mask, level+1);
	if (digit(mask, level) == 0) f_search_mask1(r->zero, mask, level + 1);
	if (mask & r->key == mask) cout << r->key << "\t" << r->data << endl;
}

template <class D>
void f_search_mask2(DSNode<D>* r, int base, int mask, int level) {
	if (r == nullptr) return;
	if (digit(mask, level) == 0) {
		f_search_mask2(r->zero, base, mask, level + 1);
		f_search_mask2(r->one, base, mask, level + 1);
	}
	else if (digit(base, level) == 1) f_search_mask2(r->one, base, mask, level + 1);
	else f_search_mask2(r->zero, base, mask, level + 1);
	if ((r->key & mask) == (base & mask)) cout << r->key << "\t" << r->data << endl;
}

template <class D>
DSNode<D>* copy(DSNode<D>* r) {
	if (r == nullptr) return nullptr;
	DSNode<D>* p = new DSNode<D>(r->key, r->data);
	p->zero = copy(r->zero);
	p->one = copy(r->one);
	return p;
}

template <class D>
struct DSTree {
	DSNode<D>* root;
	DSTree(DSNode<D>* r): root(r) {}
	DSTree(): root(nullptr) {}
	DSTree(const DSTree& t) {
		root = copy(t.root);
	}
	~DSTree() {
		f_del(root);
	}
	DSTree<D>& operator = (const DSTree& t) {
		if (this == &t) return *this;
		root = copy(t.root);
		return *this;
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
	void searchMask1(int mask) {
		f_search_mask1(root, mask, 0);
	}
	void searchMask2(int base, int mask) {
		f_search_mask2(root, base, mask, 0);
	}
	void replace() {
		DSNode<D>* r;
		D d;
		for (int n = 1; n < 8; n++) {
			r = f_search(root, 3 * n + 5, 0);
			if (r == nullptr) continue;
			d = r->data;
			f_delete(root, 3*n + 5, 0);
			f_insert(root, 10 - n, d, 0);
		}
	}
	bool check() {
		return f_check(root, 0, 0);
	}
};

template <class D>
void table_print(DSNode<D>* r) {
	if (r == nullptr) return;
	cout << r->key << "\t" << r->data << endl;
	table_print(r->zero);
	table_print(r->one);
}

void count_numbers() {
	string name;
	cin >> name;
	ifstream source(name);
	DSTree<int> tree;
	DSNode<int>* n;
	int x;
	while (source >> x) {
		n = tree.search(x);
		if (n == nullptr) tree.insert(x, 1);
		else n->data += 1;
	}
	table_print(tree.root);
	tree.print();
}

template <class D>
void add(DSTree<D> &t, DSNode<D>* r) {
	if (r == nullptr) return;
	t.insert(r->key, r->data);
	add(t, r->zero);
	add(t, r->one);
}

template <class D>
DSTree<D> merge(DSTree<D> t1, DSTree<D> t2) {
	DSTree<D> res;
	add(res, t1.root);
	add(res, t2.root);
	return res;

}

template <class D>
bool f_check(DSNode<D>* r, int level, int mask) {
	if (r == nullptr) return true;
	bool ok;
	ok =  f_check(r->zero, level+1, mask) and f_check(r->one, level + 1, mask | 1 << level);
	for (int i = 0; i < level; i++) if (digit(r->key, i) != digit(mask, i)) return false;
	return ok;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	DSTree<int> tree, t1, t2;
	int k, d;
	for (int i = 0; i < 5; i++) {
		k = rand() % 1000;
		d = rand() % 1000;
		t1.insert(k, d);
	}
	for (int i = 0; i < 5; i++) {
		k = rand() % 1000;
		d = rand() % 1000;
		t2.insert(k, d);
	}
	t1.print();
	cout << endl;
	t2.print();
	cout << endl;
	tree = merge(t1, t2);
	cout << "merged" << endl;
	tree.insert(11, 562);
	tree.insert(26, 55);
	tree.print();
	cout << "Odd keys" << endl;
	tree.searchMask1(1);
	cout << "Even keys" << endl;
	tree.searchMask2(2, 1);
	tree.replace();
	tree.print();
	return EXIT_SUCCESS;
}
