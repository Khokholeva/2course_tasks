#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

struct SNode {
	int data, key;
	SNode* left, * right;
	SNode(int k, int d, SNode* l = nullptr, SNode* r = nullptr) : key(k), data(d), left(l), right(r) {}

};

void f_print(SNode* r, int d = 0)
{
	if (r == nullptr) return;
	f_print(r->right, d + 3);
	for (int i = 0; i < d; i++)
		cout << ' ';
	cout << r->key << endl;
	f_print(r->left, d + 3);
}

void f_del(SNode*& p)
{
	if (p == nullptr)
		return;
	f_del(p->left);
	f_del(p->right);
	delete p;
	p = nullptr;
}

SNode* f_search(SNode* r, int k) {
	if (r == nullptr) return nullptr;
	if (r->key == k) return r;
	if (r->key > k) return f_search(r->left, k);
	return f_search(r->right, k);
}

void f_insert(SNode*& r, int k, int d) {
	if (r == nullptr) {
		r = new SNode(k, d);
		return;
	}
	if (r->key == k) {
		cout << "Error: key already exists" << endl;
		return;
	}
	if (r->key > k) {
		f_insert(r->left, k, d);
	}
	else f_insert(r->right, k, d);
}

void f_delete(SNode*& r, int k) {
	if (r == nullptr) return;
	if (r->key == k) {
		if (r->left == nullptr) {
			SNode* n = r->right;
			delete r;
			r = n;
			return;
		}
		if (r->right == nullptr) {
			SNode* n = r->left;
			delete r;
			r = n;
			return;
		}
		SNode* prev = nullptr;
		SNode* n = r->right;
		while (n->left != nullptr) { 
			prev = n;
			n = n->left;
		}
		r->key = n->key;
		r->data = n->data;
		if (prev == nullptr) r->right = n->right;
		else prev->left = n->right;
		delete n;
		return;
	}
	if (r->key > k) return f_delete(r->left, k);
	return f_delete(r->right, k);
}

bool f_check(SNode* r, int min_k=INT32_MIN, int max_k=INT32_MAX) { 
	if (r == nullptr) return true;
	if (r->data < min_k or r->data > max_k) return false;
	return f_check(r->left, min_k, r->data - 1) and f_check(r->right, r->data + 1, max_k);
}

struct STree
{
	SNode* root;
	STree() : root(nullptr) {}
	STree(SNode* p) : root(p) {}
	STree(int k, int d, SNode* left = nullptr, SNode* right = nullptr) : root(new SNode(k, d, left, right)) {}
	~STree() {
		f_del(root);
	}
	void print()
	{
		f_print(root);
	}
	SNode* search_rec(int k) {
		return f_search(root, k);
	}
	SNode* search_cyc(int k) {
		SNode* p = root;
		while (p != nullptr) {
			if (p->key == k) return p;
			if (p->key < k) p = p->right;
			else if (p->key > k) p = p->left;
		}
		return nullptr;
	}
	void insert_rec(int k, int d) {
		f_insert(root, k, d);
	}
	void insert_cyc(int k, int d) {
		SNode** p = &root;
		while (*p != nullptr) {
			if ((*p)->key == k) {
				cout << "Error: key already exists" << endl;
				return;
			}
			if ((*p)->key < k) p = &((*p)->right);
			else if ((*p)->key > k) p = &((*p)->left);
		}
		*p = new SNode(k, d);
	}
	void delete_rec(int k) {
		f_delete(root, k);
	}
	void delete_cyc(int k) {
		SNode* r = root;
		SNode* par = nullptr;
		int side = 0;
		while (r != nullptr) {
			if (r->key == k) break;
			par = r;
			if (r->key < k) { r = r->right; side = 1; }
			else if (r->key > k) { r = r->left; side = 0; }
		}
		if (r == nullptr) return;
		if (r->left == nullptr) {
			if (par != nullptr) {
				if (side == 0) par->left = r->right;
				else par->right = r->right;
			}
			else root = r->right;
			delete r;
			return;
		}
		if (r->right == nullptr) {
			if (par != nullptr) {
				if (side == 0) par->left = r->left;
				else par->right = r->left;
			}
			else root = r->left;
			delete r;
			return;
		}
		SNode* n = r->right;
		SNode* prev = nullptr;
		while (n->left != nullptr) {
			prev = n;
			n = n->left;
		}
		r->key = n->key;
		r->data = n->data;
		if (prev == nullptr) r->right = n->right;
		else prev->left = n->right;
		delete n;
		return;
	}
	bool check() {
		return f_check(root, INT32_MIN, INT32_MAX);
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	SNode* p12 = new SNode(12, 12),
		* p10 = new SNode(10, 10),
		* p11 = new SNode(11, 11, p10, p12),
		* p9 = new SNode(9, 9, nullptr, p11),
		* p4 = new SNode(4, 4),
		* p3 = new SNode(3, 3, nullptr, p4),
		* p6 = new SNode(6, 6),
		* p5 = new SNode(5, 5, p3, p6),
		* p7 = new SNode(7, 7, p5),
		* p1 = new SNode(1, 1),
		* p2 = new SNode(2, 2, p1, p7),
		* p8 = new SNode(8, 8, p2, p9);
	STree t(p8);
	t.print();
	cout << endl << endl;
	t.delete_cyc(8);
	t.delete_rec(2);
	t.print();
	cout << endl << endl;
	cout << boolalpha << t.check() << endl;
	p6->key = 8;
	p6->data = 8; 
	t.print();
	cout << endl << endl;
	cout << boolalpha << t.check() << endl;

	return EXIT_SUCCESS;
}
