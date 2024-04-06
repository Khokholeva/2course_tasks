#include <iostream>
#include <cstdlib>
using namespace std;

struct SNode {
	int data, key;
	SNode* left, * right;
	SNode(int k, int d, SNode * l = nullptr, SNode * r = nullptr) : key(k), data(d), left(l), right(r) {}

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

struct STree
{
	SNode* root;
	STree() : root(nullptr){}
	STree(SNode* p) : root(p) {}
	STree(int k, int d, SNode* left = nullptr, SNode* right = nullptr) : root(new SNode(k, d,left, right)) {}
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
};


int main()
{
	setlocale(LC_ALL, "Russian");
	srand((unsigned)time(0));
	int k;
	STree tree1, tree2;
	for (int i = 1; i < 11; i++) {
		k = rand() % 100;
		cout << k << ": " << i << endl;
		tree1.insert_cyc(k, i);
		tree2.insert_rec(k, i);
	}
	cout << endl;
	cout << "cyc tree:" << endl;
	tree1.print();
	cout << endl;
	cout << "rec tree:" << endl;
	tree2.print();
	cout << endl;
	SNode* p;
	for (int i = 0; i < 5; i++) {
		cin >> k;
		p = tree1.search_cyc(k);
		if (p != nullptr) cout << "cyc found " <<p->data << endl;
		else cout << "cyc: No key" << endl;
		p = tree2.search_rec(k);
		if (p != nullptr) cout << "rec found " << p->data << endl;
		else cout << "rec: No key" << endl;
	}
	return EXIT_SUCCESS;
}
