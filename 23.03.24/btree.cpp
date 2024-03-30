#include <iostream>
#include <cstdlib>
using namespace std;

struct BNode
{
	int data;
	BNode* left, * right;
	BNode(int d, BNode* l = nullptr, BNode* r = nullptr): data(d), left(l), right(r) {} 

};

void f_print(BNode* r, int d = 0)
{
	if (r == nullptr) return;
	f_print(r->right, d + 3);
	for (int i = 0; i < d; i++)
		cout << ' ';
	cout << r->data << endl;
	f_print(r->left, d + 3);
}

struct BTree
{
	BNode* root;
	BTree(BNode* p) : root(p) {}
	BTree(int d, BNode *left = nullptr, BNode *right = nullptr): root(new BNode(d, left, right)) {}

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
		BNode *p = root->left;
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
		BNode* l = root->left,* r = root->right;
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
		BNode* p = root, *q = nullptr;
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
};



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
	cout << endl;
	tree.changeLRoot();
	tree.print();
	cout << endl;
	tree.rotateLeft();
	tree.print();
	cout << endl;
	
	return EXIT_SUCCESS;
}
