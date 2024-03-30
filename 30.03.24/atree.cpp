#include <iostream>
#include <cstdlib>
using namespace std;


struct ANode {
	int data;
	ANode* son, *brother;
	ANode(int d, ANode* s = nullptr, ANode* b = nullptr) : data(d), son(s), brother(b) {}
};

void print(struct ANode* r, int offset=0)
{
	if (r == 0) return;
	for (int i = 0; i < offset; i++)
		printf(" ");
	printf("%d\n", r->data);
	print(r->son, offset + 3);
	print(r->brother, offset);
}

struct ATree {
	ANode* root;
	ATree(ANode* p) : root(p) {}
	ATree(int d, ANode* s = nullptr, ANode* b = nullptr) : root(new ANode(d, s, b)) {}
	int grChCount() {
		int count = 0;
		ANode* s = root->son;
		while (s != nullptr) {
			ANode* g = s->son;
			while (g != nullptr) {
				count++;
				g = g->brother;
			}
			s = s->brother;
		}
		return count;
	}
	ANode* specificSon(int d1, int d2) {
		ANode* s = root->son;
		while (s != nullptr) {
			if (s->data == d1) {
				ANode* g = s->son;
				while (g != nullptr) {
					if (g->data == d2) return s;
					g = g->brother;
				}
			}
			s = s->brother;
		}
		return nullptr;
	}
	ANode* steps(int* path, int size) {
		ANode* p = root;
		int count;
		for (int i = 0; i < size; i++) {
			if (path[i] < 1) { cout << "Error: invalid path" << endl; return nullptr; }
			count = path[i];
			p = p->son;
			count--;
			while (p != nullptr and count > 0) {
				p = p->brother;
				count--;
			}
			if (p == nullptr) { cout << "Error: invalid path" << endl; return nullptr; }
		}
		
		return p;
	}
	void flatten() {
		ANode *s = root->son, *b, *g;
		ANode *base = new ANode(0);
		ANode* edge = base;
		while (s != nullptr) {
			g = s->son;
			if (g != nullptr) {
				edge->brother = g;
			}
			while (edge->brother != nullptr) edge = edge->brother;
			b = s->brother;
			delete s;
			s = b;
		}
		root->son = base->brother;
		
	}

};

int main()
{
	setlocale(LC_ALL, "Russian");

	ANode* a10 = new ANode(10),
		* a9 = new ANode(9, nullptr, a10),
		* a8 = new ANode(8),
		* a7 = new ANode(7),
		* a6 = new ANode(6, nullptr, a7),
		* a5 = new ANode(5, nullptr, a6),
		* a4 = new ANode(4, a9),
		* a3 = new ANode(3, a8, a4),
		* a2 = new ANode(2, a5, a3),
		* a1 = new ANode(1, a2);
	print(a1);
	ATree tree(a1);
	cout << "grandchildren: " << tree.grChCount() << endl;
	tree.flatten();
	print(a1);
	return EXIT_SUCCESS;
}
