#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

template <class D>
struct AVLNode {
	int key;
	D data;
	AVLNode* left, * right;
	AVLNode* parent;
	int height;
	AVLNode(int k, D d, AVLNode* l = nullptr, AVLNode* r = nullptr, AVLNode* p = 0, int h = 0) : key(k), data(d), left(l), right(r), parent(p), height(h) {}

	void correct_h() {
		int a = 0, b = 0;
		if (left != nullptr) a = left->height;
		if (right != nullptr) b = right->height;
		height = (a > b ? a : b) + 1;
	}
	int defect_h() {
		int a = 0, b = 0;
		if (left != nullptr) a = left->height;
		if (right != nullptr) b = right->height;
		return a - b;
	}
	void print() {
		cout << "Node at " << this << endl;
		cout << "   key: " << key << endl;
		cout << "   data: " << data << endl;
		cout << "   height: " << height << endl;
		cout << "   parent: " << parent << endl;
		cout << "   left: " << left << endl;
		cout << "   right: " << right << endl;

	}
};

template <class D>
AVLNode<D>* copy(AVLNode<D>* r) {
	if (r == nullptr) return nullptr;
	AVLNode<D>* p = new AVLNode<D>(r->key, r->data);
	p->left = copy(r->left);
	p->right = copy(r->right);
	p->correct_h();
	if (p->left != nullptr) p->left->parent = p;
	if (p->right != nullptr) p->right->parent = p;
	return p;
}

template <class D>
void f_del(AVLNode<D>*& p) {
	if (p == nullptr)
		return;
	f_del(p->left);
	f_del(p->right);
	delete p;
	p = nullptr;
}

template <class D>
void f_print(AVLNode<D>* r, int d = 0)
{
	if (r == nullptr) return;
	f_print(r->right, d + 1);
	for (int i = 0; i < d; i++) cout << "   ";
	cout << r->key << endl;
	f_print(r->left, d + 1);
}

template <class D>
bool f_test(AVLNode<D>* r, int min_k = INT32_MIN, int max_k = INT32_MAX) {
	if (r == nullptr) return true;
	if (r->key < min_k or r->key > max_k or abs(r->defect_h()) > 1) return false;
	return f_test(r->left, min_k, r->key - 1) and f_test(r->right, r->key + 1, max_k);
}

template <class D>
struct AVLTree {
	AVLNode<D>* root;
	AVLTree() : root(nullptr) {}
	AVLTree(const AVLTree& t) {
		root = copy(t.root);
	}
	AVLTree<D>& operator = (const AVLTree& t) {
		if (this == &t) return *this;
		root = copy(t.root);
		return *this;
	}
	~AVLTree() {
		f_del(root);
	}
	void print() {
		f_print(root);
	}
	AVLNode<D>* search(int k) {
		AVLNode<D>* p = root;
		while (p != nullptr) {
			if (p->key == k) return p;
			if (p->key < k) p = p->right;
			else if (p->key > k) p = p->left;
		}
		return nullptr;
	}
	void rotateLeft(AVLNode<D>* base) {
		
		AVLNode<D>* r = base->right;
		AVLNode<D>* r_l = r->left;
		AVLNode<D>* par = base->parent;
		base->right = r_l;
		if (r_l != nullptr) r_l->parent = base;
		r->left = base;
		base->parent = r;
		r->parent = par;
		if (base == root) root = r;
		else {
			if (par->left == base) par->left = r;
			else par->right = r;
		}
		base->correct_h();
		base->parent->correct_h();
		
	}
	void rotateRight(AVLNode<D>* base) {

		AVLNode<D>* l = base->left;
		AVLNode<D>* l_r = l->right;
		AVLNode<D>* par = base->parent;
		base->left = l_r;
		if (l_r != nullptr) l_r->parent = base;
		l->right = base;
		base->parent = l;
		l->parent = par;
		if (base == root) root = l;
		else {
			if (par->left == base) par->left = l;
			else par->right = l;
		}
		base->correct_h();
		base->parent->correct_h();
		
	}
	void correctm2(AVLNode<D>*& base) {
		if ((base->right)->defect_h() <= 0)rotateLeft(base);
		else {
			rotateRight(base->right);
			rotateLeft(base);
		}
	}
	void correct2(AVLNode<D>*& base) {
		if ((base->left)->defect_h() >= 0) rotateRight(base);
		else {
			rotateLeft(base->left);
			rotateRight(base);
		}
	}
	void rebalance(AVLNode<D>* base) {
		if (base == nullptr) return;
		
		int bf = base->defect_h();
		if (bf == -2) correctm2(base);
		else if (bf == 2) correct2(base);
		base->correct_h();
		rebalance(base->parent);
	}
	void insert(int k, D d) {
		
		AVLNode<D>** p = &root;
		AVLNode<D>* prev = nullptr;
		while (*p != nullptr) {
			if ((*p)->key == k) {
				//cout << "Error: key already exists" << endl;
				return;
			}
			prev = *p;
			if ((*p)->key < k) p = &((*p)->right);
			else if ((*p)->key > k) p = &((*p)->left);
		}
		*p = new AVLNode<D>(k, d, nullptr, nullptr, prev, 1);
		
		if (prev != nullptr and prev->height == 1) rebalance((*p)->parent);
	}
	void del_root_left(AVLNode<D>* r) {
		root = r->left;
		if (root != nullptr) root->parent = nullptr;
		delete r;
	}
	void del_root_right(AVLNode<D>* r) {
		root = r->right;
		if (root != nullptr) root->parent = nullptr;
		delete r;
	}
	void del_left_left(AVLNode<D>* r) {
		r->parent->left = r->left;
		if (r->left != nullptr) r->left->parent = r->parent;
		rebalance(r->parent);
		delete r;
	}
	void del_left_right(AVLNode<D>* r) {
		r->parent->left = r->right;
		if (r->right != nullptr) r->right->parent = r->parent;
		rebalance(r->parent);
		delete r;
	}
	void del_right_left(AVLNode<D>* r) {
		r->parent->right = r->left;
		if (r->left != nullptr) r->left->parent = r->parent;
		rebalance(r->parent);
		delete r;
	}
	void del_right_right(AVLNode<D>* r) {
		r->parent->right = r->right;
		if (r->right != nullptr) r->right->parent = r->parent;
		rebalance(r->parent);
		delete r;
	}
	void delele(int k) {
		AVLNode<D>* r = root;
		while (r != nullptr) {
			if (r->key == k) break;
			if (r->key < k) r = r->right;
			else if (r->key > k) r = r->left;
		}
		if (r == nullptr) return;
		if (r->left != nullptr and r->right != nullptr) {
			AVLNode<D>* n = r->right;
			while (n->left != nullptr) n = n->left;
			r->key = n->key;
			r->data = n->data;
			if (n->parent == r) del_right_right(n);
			else del_left_right(n);
			return;
		}
		if (r == root) {
			if (r->right == nullptr) del_root_left(r);
			else del_root_right(r);
			return;
		}
		if (r == r->parent->left) {
			if (r->right == nullptr) del_left_left(r);
			else del_left_right(r);
			return;
		}
		if (r->right == nullptr) del_right_left(r);
		else del_right_right(r);
	}
	bool test() {
		return f_test(root);
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	int seed = time(0);
	cout << seed << endl;
	srand(seed);
	bool x;
	AVLTree<int> test;
	for (int i = 0; i < 1000; i++) {
		test.insert(rand(), i);
		x = test.test();
		if (not x) {
			cout << "Error" << endl;
			break;
		}
	}
	AVLNode<int>* n;
	int d;
	for (int i = 0; i < 1000; i++) {
		d = rand();
		n = test.search(d);
		if (n != nullptr) test.delele(d);
		x = test.test();
		if (not x) {
			cout << "Error" << endl;
			break;
		}
	}
	cout << "Test ok" << endl;

	AVLTree<int> t;
	for (int i = 0; i < 20; i++) {
		t.insert(rand()%100, i);
	}
	t.print();
	cout << endl << endl;
	int k;
	cin >> k;
	t.delele(k);
	cout << endl;
	t.print();
	cout << endl;
	return EXIT_SUCCESS;
}
