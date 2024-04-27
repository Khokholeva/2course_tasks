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
	AVLNode(int k, D d, AVLNode* l = nullptr, AVLNode* r = nullptr, AVLNode* p = 0, int h = 0): key(k), data(d), left(l), right(r), parent(p), height(h) {}

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
struct AVLTree {
	AVLNode<D>* root;
	AVLTree(): root(nullptr) {}
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
	void rotateLeft(AVLNode<D>*& base) {
		AVLNode<D>* r = base->right;
		base->right = r->left;
		if (base->right != nullptr) base->right->parent = base;
		r->left = base;
		if (base == root) root = r;
		else {
			if (base->parent->right == base) base->parent->right = r;
			else base->parent->left = r;
		}
		base = r;
		base->parent = base->left->parent;
		base->left->correct_h();
		base->correct_h();
	}
	void rotateRight(AVLNode<D>*& base) {
		AVLNode<D>* l = base->left;
		base->left = l->right;
		if (base->left != nullptr) base->left->parent = base;
		l->right = base;
		if (base == root) root = l;
		else {
			if (base->parent->right == base) base->parent->right = l;
			else base->parent->left = l;
		}
		base = l;
		base->parent = base->right->parent;
		base->right->correct_h();
		base->correct_h();
	}
	void correctm2(AVLNode<D>*& base) {
		if ((base->right)->defect_h() <= 0) rotateLeft(base);
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
		base->correct_h();
		int bf = base->defect_h();
		if (bf == -2) correctm2(base);
		else if (bf == 2) correct2(base);
		else rebalance(base->parent);
	}
	void insert(int k, D d) {
		AVLNode<D>** p = &root;
		AVLNode<D>* prev = nullptr;
		while (*p != nullptr) {
			if ((*p)->key == k) {
				cout << "Error: key already exists" << endl;
				return;
			}
			prev = *p;
			if ((*p)->key < k) p = &((*p)->right);
			else if ((*p)->key > k) p = &((*p)->left);
		}
		*p = new AVLNode<D>(k, d, nullptr, nullptr, prev, 1);
		if (prev != nullptr and prev->height == 1) rebalance((*p)->parent);
	}
};


int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	AVLTree<int> t;
	for (int i = 0; i < 20; i++) {
		t.insert(i, i);
	}
	t.print();
	cout << endl;
	return EXIT_SUCCESS;
}
