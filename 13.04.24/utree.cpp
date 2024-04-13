#include <iostream>
#include <cstdlib>
using namespace std;

struct UNode {
	int data;
	UNode* left, * right, *parent;
	UNode(int d, UNode* l = nullptr, UNode* r = nullptr, UNode* p = nullptr) : data(d), left(l), right(r), parent(p) {}
};

struct UTree {
	UNode* root;
	UTree(UNode* p) : root(p) {}
	UTree(int d, UNode* left = nullptr, UNode* right = nullptr, UNode* parent = nullptr) : root(new UNode(d, left, right, parent)) {}
	~UTree() {
		f_del(root);
	}
	void rotateLeft() {
		UNode* r = root->right;
		root->right = r->left;
		root->parent = r;
		root->right->parent = root;
		r->left = root;
		r->parent = nullptr;
		root = r;
	}

	void delNode(UNode*& r) {
		if (r == nullptr) return;
		UNode* p = r->parent;
		UNode* c;
		if (r->left != nullptr) c = r->left;
		else c = r->right;
		if (c != nullptr) c->parent = p;
		if (p->left == r) p->left = c;
		else p->right = c;
		delete r;
		r = nullptr;
	}
	void print()
	{
		f_print(root);
	}
	static void f_del(UNode*& r);
	static void f_print(UNode* r, int d = 0);

};

void UTree::f_del(UNode*& p)
{
	if (p == nullptr) 
		return;
	f_del(p->left); 
	f_del(p->right); 
	delete p;
	p = nullptr; 
}
void UTree::f_print(UNode* r, int d)
{
	if (r == nullptr) return;
	f_print(r->right, d + 3);
	for (int i = 0; i < d; i++)
		cout << ' ';
	cout << r->data;
	if (r->parent != nullptr) cout << "(" << r->parent->data << ")";
	cout << endl;
	f_print(r->left, d + 3);
}

int main()
{
	setlocale(LC_ALL, "Russian");

	UNode
		* p8 = new UNode(8),
		* p7 = new UNode(7),
		* p6 = new UNode(6, p7, p8),
		* p5 = new UNode(5),
		* p4 = new UNode(4),
		* p3 = new UNode(3, p6),
		* p2 = new UNode(2, p4, p5),

		* p1 = new UNode(1, p2, p3);
	p8->parent = p6;
	p7->parent = p6;
	p6->parent = p3;
	p5->parent = p2;
	p4->parent = p2;
	p3->parent = p1;
	p2->parent = p1;
	UTree t(p1);
	t.print();
	t.delNode(p3);
	cout << endl;
	t.print();
	t.rotateLeft();
	cout << endl;
	t.print();
	return EXIT_SUCCESS;
}
