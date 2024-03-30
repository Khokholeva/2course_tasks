#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

struct BNode
{
	int data;
	BNode* left, * right;
	BNode(int d, BNode* l = nullptr, BNode* r = nullptr) : data(d), left(l), right(r) {}

};

struct BTree
{
	BTree(BNode* p) : root(p) {}
	BTree(int d, BNode* left = nullptr, BNode* right = nullptr) : root(new BNode(d, left, right)) {}

	void print()
	{
		f_print(root);
	}
	void attachLeft() {
		root->left = new BNode(0);
	}
	void attachL_R() {
		root->left = new BNode(0);
		root->right = new BNode(0);
	}
	void delLeft() {
		BNode* l = root->left;
		delete l;
		root->left = nullptr;
	}
	void delL_R() {
		BNode* l = root->left;
		delete l;
		root->left = nullptr;
		BNode* r = root->left;
		delete r;
		root->right = nullptr;
	}
	void delRoot() {
		BNode* p = root;
		root = root->left;
		delete p;
	}
	void changeL_R() {
		BNode* p = root->left;
		root->left = root->right;
		root->right = p;
	}
	void insertRoot(int d = 0) {
		BNode* new_r = new BNode(d, root);
		root = new_r;
	}
	void insertUnderRoot1(double d = 0) {
		BNode* new_l = new BNode(d, root->left);
		root->left = new_l;
	}
	void insertUnderRoot2(double d = 0) {
		BNode* new_l = new BNode(d, root->left, root->right);
		root->left = new_l;
		root->right = nullptr;
	}
	void changeLRoot() {
		BNode* l = root->left, * r = root->right;
		root->left = l->left;
		root->right = l->right;
		l->left = root;
		l->right = r;
		root = l;
	}
	void rotateLeft() {
		BNode* r = root->right;
		root->right = r->left;
		r->left = root;
		root = r;
	}
	BNode* getLeftmost() {
		BNode* p = root;
		while (p->left != nullptr) p = p->left;
		return p;
	}
	void insertLeftmost() {
		BNode* p = this->getLeftmost();
		p->left = new BNode(0);
	}
	void delLefmost() {
		BNode* p = root;
		BNode* q = nullptr;
		while (p->left != nullptr) {
			q = p;
			p = p->left;
		}

		if (q == nullptr) root = p->right;
		else q->left = p->right;
		delete p;
	}
	BNode* steps() {
		BNode* p = root;
		while (p->right != nullptr) {
			p = p->right;
			if (p->left != nullptr) p = p->left;
			else break;
		}
		return p;
	}
	BNode* getLeftmostLeaf() {
		BNode* p = root;
		while (p->left != nullptr or p->right != nullptr) {
			if (p->left != nullptr) p = p->left;
			else p = p->right;
		}
		return p;
	}
	void delLeftmostLeaf() {
		BNode* p = root;
		BNode* q = nullptr;
		while (p->left != nullptr or p->right != nullptr) {
			q = p;
			if (p->left != nullptr) p = p->left;
			else p = p->right;
		}
		if (q != nullptr and q->left != nullptr) q->left = nullptr;
		else if (q != nullptr) q->right = nullptr;
		else root = nullptr;
		delete p;
	}
	BNode* getSecLeftLeaf() {
		BNode* p = root, * q = nullptr;
		while (p->left != nullptr or p->right != nullptr) {
			if (p->left != nullptr and p->right != nullptr) q = p;
			if (p->left != nullptr) p = p->left;
			else p = p->right;
		}
		if (q == nullptr) {
			cout << "No second leaf" << endl;
			return q;
		}
		p = q->right;
		while (p->left != nullptr or p->right != nullptr) {
			if (p->left != nullptr) p = p->left;
			else p = p->right;
		}
		return p;
	}
	void scale() {
		f_scale(root);
	}
	int sum() {
		return f_sum(root);
	}
	int count_neg() {
		return f_count_neg(root);
	}
	int height() {
		return f_height(root);
	}
	void reflect() {
		return f_reflect(root);
	}
	int mult() {
		return f_mult(root);
	}
	int eval() {
		return f_eval(root);
	}
	BNode* find(int d) {
		return f_find(root, d);
	}
	int min() {
		return f_min(root);
	}

	private:
		BNode* root;
		static void f_print(BNode* r, int d = 0);
		static void f_scale(BNode* r);
		static int f_sum(BNode* r);
		static int f_count_neg(BNode* r);
		static int f_height(BNode* r);
		static void f_reflect(BNode* r);
		static int f_mult(BNode* r);
		static int f_eval(BNode* r);
		static BNode* f_find(BNode* r, int d);
		static int f_min(BNode* r);

};

void BTree::f_print(BNode* r, int d)
{
	if (r == nullptr) return;
	f_print(r->right, d + 3);
	for (int i = 0; i < d; i++)
		cout << ' ';
	cout << r->data << endl;
	f_print(r->left, d + 3);
}
void BTree::f_scale(BNode* r) {
	if (r == nullptr) return;
	r->data *= 3;
	f_scale(r->left);
	f_scale(r->right);
}
int BTree::f_sum(BNode* r) {
	if (r == nullptr) return 0;
	return r->data + f_sum(r->left) + f_sum(r->right);
}
int BTree::f_count_neg(BNode* r) {
	if (r == nullptr) return 0;
	int d = r->data < 0 ? 1 : 0;
	return f_count_neg(r->left) + f_count_neg(r->right) + d;
}
int BTree::f_height(BNode* r) {
	if (r == nullptr) return 0;
	int a = f_height(r->left) + 1, b = f_height(r->right) + 1;
	return a > b ? a : b;
}
void BTree::f_reflect(BNode* r) {
	if (r == nullptr) return;
	f_reflect(r->right);
	f_reflect(r->left);
	BNode* p = r->right;
	r->right = r->left;
	r->left = p;
}
int BTree::f_mult(BNode* r) {
	if (r == nullptr) return 1;
	if (r->right != nullptr and r->left != nullptr) {
		return r->data * f_mult(r->right) * f_mult(r->left);
	}
	return 1;
}
int BTree::f_eval(BNode* r) {
	if (r->right == nullptr) return r->data;
	if (r->data == 1) return f_eval(r->left) + f_eval(r->right);
	if (r->data == 2) return f_eval(r->left) - f_eval(r->right);
	if (r->data == 3) return f_eval(r->left) * f_eval(r->right);
	if (r->data == 4) return f_eval(r->left) / f_eval(r->right);
}
BNode* BTree::f_find(BNode* r, int d) {
	if (r == nullptr) return nullptr;
	if (r->data == d) return r;
	BNode* p = f_find(r->left, d);
	if (p != nullptr) return p;
	BNode* q = f_find(r->right, d);
	return q;
}
int BTree::f_min(BNode* r) {
	int a = r->data, b = r->data;
	if (r->left != nullptr) a = f_min(r->left);
	if (r->right != nullptr) b = f_min(r->right);
	return (r->data < a and r->data < b) ? r->data : (a < b ? a : b);
}

BNode* form_tree(string data) {
	int a, b, c, d;
	int counter = 0;
	a = data.find_first_of("(");
	d = data.find_first_of("(,", a + 1);
	if (d != -1 and data[d] == '(') counter = 1;
	else d = 0;
	while (counter != 0) {
		d = data.find_first_of("()", d + 1);
		if (data[d] == '(') counter++;
		else counter--;
	}
	b = data.find_first_of(",", d);
	c = data.find_last_of(")");
	if (a == -1) return nullptr;
	int val = stoi(data.substr(0, a));
	BNode* l = form_tree(data.substr(a + 1, b - a - 1));
	BNode* r = form_tree(data.substr(b + 1, c - b - 1));
	return new BNode(val, l, r);
}

BNode* input() {
	string data;
	cin >> data;
	return form_tree(data);
}
int main()
{
	setlocale(LC_ALL, "Russian");
	BNode* p7 = new BNode(7),
		* p6 = new BNode(6),
		* p5 = new BNode(5),
		* p4 = new BNode(4),
		* p3 = new BNode(3, p6, p7),
		* p2 = new BNode(2, p4, p5),
		* p1 = new BNode(1, p2, p3);
	BTree tree(p1);
	tree.print();
	cout << "sum = " << tree.sum() << endl;
	cout << "mult = " << tree.mult() << endl;
	cout << "eval = " << tree.eval() << endl;
	tree.scale();
	tree.rotateLeft();
	tree.print();
	tree.reflect();
	tree.print();
	cout << "height: " << tree.height() << endl;
	cout << "min: " << tree.min() << endl;

	cout << endl;
	BNode* q = input();
	BTree tree2(q);
	tree2.print();
	//1(2(4(.,.),.),3(.,5(6(.,.),7(.,.))))
	return EXIT_SUCCESS;
}
