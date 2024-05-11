#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

struct SNode {
	int data, key;
	SNode* left, * right, *parent;
	SNode(int k, int d, SNode* l = nullptr, SNode* r = nullptr, SNode* p = nullptr) : key(k), data(d), left(l), right(r), parent(p) {}

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
		r->left->parent = r;
	}
	else {
		f_insert(r->right, k, d);
		r->right->parent = r;
	}
}

void f_delete(SNode*& r, int k) {
	if (r == nullptr) return;
	if (r->key == k) {
		if (r->left == nullptr) {
			SNode* n = r->right;
			n->parent = r->parent;
			delete r;
			r = n;
			return;
		}
		if (r->right == nullptr) {
			SNode* n = r->left;
			n->parent = r->parent;
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
		if (prev == nullptr) { r->right = n->right; n->right->parent = r; }
		else { prev->left = n->right; n->right->parent = prev; }
		delete n;
		return;
	}
	if (r->key > k) return f_delete(r->left, k);
	return f_delete(r->right, k);
}

bool f_check(SNode* r, int min_k = INT32_MIN, int max_k = INT32_MAX) {
	if (r == nullptr) return true;
	if (r->data < min_k or r->data > max_k) return false;
	return f_check(r->left, min_k, r->data - 1) and f_check(r->right, r->data + 1, max_k);
}

void find_error(SNode* r, int& k, int& d) {
	if (r == nullptr) return;
	if (r->left != nullptr and r->left->key > r->key) {
		k = r->left->key;
		d = r->left->data;
		delete r->left;
		r->left = nullptr;
		return;
	}
	if (r->right != nullptr and r->right->key < r->key) {
		k = r->right->key;
		d = r->right->data;
		delete r->right;
		r->right = nullptr;
		return;
	}
	find_error(r->right, k, d);
	find_error(r->left, k, d);
}

struct STree
{
	SNode* root;
	STree() : root(nullptr) {}
	STree(SNode* p) : root(p) {}
	STree(int k, int d, SNode* left = nullptr, SNode* right = nullptr, SNode* parent = nullptr) : root(new SNode(k, d, left, right, parent)) {}
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
		SNode* prev = nullptr;
		while (*p != nullptr) {
			if ((*p)->key == k) {
				cout << "Error: key already exists" << endl;
				return;
			}
			prev =* p;
			if ((*p)->key < k) p = &((*p)->right);
			else if ((*p)->key > k) p = &((*p)->left);
		}
		*p = new SNode(k, d);
		(*p)->parent = prev;
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
	void find_nearest(int k, SNode*& low, SNode*& high) {
		SNode* r = root;
		SNode* last_h = nullptr;
		SNode* last_l = nullptr;
		while (r != nullptr) {
			if (r->key == k) {
				low = r;
				high = r;
				return;
			}
			if (r->key > k) {
				last_h = r;
				r = r->left;
			}
			else {
				last_l = r;
				r = r->right;
			}
		}
		low = last_l;
		high = last_h;
	}
	SNode* next(SNode* r) {
		if (r->right == nullptr) { 
			SNode* n = r->parent;
			while (n != nullptr) {
				if (n->left == r) return n;
				r = n;
				n = n->parent;
			}
			return n;
			
		}
		SNode* n = r->right;
		while (n->left != nullptr) n = n->left;
		return n;
	}
	void fix_leaf() {
		int k, d;
		find_error(root, k, d);
		this->insert_rec(k, d);
	}
};



void del50(SNode*& r) {
	if (r == nullptr) return;
	if (r->key > 50) {
		f_del(r->right);
		r = r->left;
		del50(r);
	}
	else del50(r->right);
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int seed = time(0);
	cout << seed << endl;
	srand(seed);
	STree t;
	for (int i = 0; i < 15; i++) {
		t.insert_rec(rand() % 100, i);
	}
	t.print();
	cout << endl << endl;
	int x;
	cout << "Getting surrounding and next in order nodes" << endl;
	cin >> x;
	SNode* a, * b;
	while (x != -1) {
		t.find_nearest(x, a, b);
		if (a == nullptr) cout << "Nearest: -" << " ";
		else cout << "Nearest: " << a->key << " ";
		if (b == nullptr) cout << "-" << endl;
		else cout << b->key << endl;
		SNode* s = t.search_rec(x);
		if (s != nullptr) {
			s = t.next(s);
			if (s == nullptr) cout << "Next: -" << endl;
			else cout << "Next: " << s->key << endl;
		}
		cin >> x;
		
	}
	//hoping that there are keys less than 30 and there is no 30 in the tree already
	SNode* p = new SNode(30, 30);
	SNode* r = t.root;
	while (r->left != nullptr) r = r->left;
	r->left = p;
	t.print();
	cout << endl << "Added 30 to the wrong place, now fixing it" << endl;
	t.fix_leaf();
	t.print();
	return EXIT_SUCCESS;
}
