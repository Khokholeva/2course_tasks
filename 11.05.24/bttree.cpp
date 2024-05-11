#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

const int N = 4;
template<class K, class T>
struct BTNode; 

template<class K, class T>
struct Item
{
	K key;
	T data;
	BTNode<K, T>* down;
};

template<class K, class T>
struct BTNode
{
	int n;
	Item<K, T> ar[N];
};

template<class K, class T>
void f_destr(BTNode<K, T>* &r) {
	if (r == nullptr) return;
	for (int i = 0; i < r->n; i++) {
		f_destr((r->ar)[i].down);
	}
	delete r;
}

template<class K, class T>
void f_print(BTNode<K, T>*r, int d = 0) {
	if (r == nullptr) return;
	Item<K, T> x;
	for (int t = 0; t < r->n; t++) {
		x = (r->ar)[t];
		for (int i = 0; i < d; i++) cout << "   ";
		if (x.down != nullptr) cout << x.key << endl;
		else cout << x.key << ": " << x.data << endl;
		f_print(x.down, d+1);
	}
}

template<class K, class T>
struct BTTree
{
	BTNode<K, T>* root;
	int height;
	BTTree() {
		root = new BTNode<K, T>;
		root->n = 0;
		height = 1;
	}
	~BTTree() {
		f_destr(root);
	}
	void print() {
		f_print(root);
	}
	Item<K, T> search(K k) {
		BTNode* r = root;
		while (r->ar[0].down != nullptr) {
			int ind = -1;
			while (ind < r->n - 1 and r->ar[ind + 1].key <= k) ind += 1;
			if (ind == -1) return nullptr;
			r = r->ar[ind].down;
		}
		for (int i = 0; i < r->n; i++) {
			if (r->ar[i].key == k) return r->ar[i];
		}
		return nullptr;
	}
	void insertB(BTNode<K, T> *p, int i, Item<K, T>x) {
		for (int j = p->n; j > i; j--) {
			p->ar[j] = p->ar[j - 1];
		}
		p->ar[i] = x;
		p->n++;
	}
	BTNode<K, T>* split(BTNode<K, T>* p) {
		BTNode<K, T>* r = new BTNode<K, T>;
		r->n = N / 2;
		p->n = N / 2;
		for (int i = 0; i < N / 2; i++) {
			r->ar[i] = p->ar[i + N / 2];
		}
		return r;
	}
	BTNode<K, T>* insertR(BTNode<K, T>* p, K k, T d, int h) {
		int pos = p->n;
		for (int i = 0; i < p->n; i++) { //first key larger than new
			if (p->ar[i].key > k) {
				pos = i;
				break;
			}
		}
		Item<K, T> res;
		res.key = k;
		res.data = d;
		res.down = nullptr;
		if (h > 1) {
			if (pos == 0) {
				pos = 1;
				p->ar[0].key = k;
			}
			BTNode<K, T>* s = insertR(p->ar[pos-1].down, k, d, h - 1);
			if (s == nullptr) return nullptr;
			res.key = s->ar[0].key;
			res.down = s;
		}
		insertB(p, pos, res);
		if (p->n < N) return nullptr;
		BTNode<K, T>* r = split(p);
		return r;
	}
	void insert(K k, T d) {
		BTNode<K, T>* res = insertR(root, k, d, height);
		if (res == nullptr) return;
		BTNode<K, T>* new_r = new BTNode<K, T>;
		new_r->n = 2;
		Item<K, T> a, b;
		a.key = root->ar[0].key;
		a.down = root;
		b.key = res->ar[0].key;
		b.down = res;
		new_r->ar[0] = a;
		new_r->ar[1] = b;
		root = new_r;
		height++;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	int seed = time(0);
	cout << "seed " << seed << endl << endl;
	srand(seed);
	BTTree<int, int> t;
	for (int i = 1; i < 16; i++) {
		t.insert(rand()% 100, i);
	}
	t.print();
	return EXIT_SUCCESS;
}
