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
		int h = height;
		while (h > 1) {
			int ind = -1;
			while (ind < r->n - 1 and r->ar[ind + 1].key <= k) ind += 1;
			if (ind == -1) return nullptr;
			r = r->ar[ind].down;
			h -= 1;
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
	void removeB(BTNode<K, T>* p, int ind) {
		for (int i = ind; i < p->n - 1; i++) {
			p->ar[i] = p->ar[i + 1];
		}
		p->n--;
	}
	void join(BTNode<K, T>* p, int n) {
		BTNode<K, T> *r = p->ar[n].down;
		BTNode<K, T> *s = p->ar[n + 1].down;
		for (int i = 0; i < s->n; i++) {
			r->ar[r->n + i] = s->ar[i];
		}
		r->n += s->n;
		delete s;
		removeB(p, n + 1);
	}
	void pass_forward(BTNode<K, T>* p, int n) {
		BTNode<K, T> *r = p->ar[n].down;
		BTNode<K, T> *s = p->ar[n + 1].down;
		Item<K, T> m = r->ar[r->n-1];
		removeB(r, r->n - 1);
		insertB(s, 0, m);
		p->ar[n + 1].key = s->ar[0].key;
		
	}
	void pass_backward(BTNode<K, T>* p, int n) {
		BTNode<K, T> *r = p->ar[n].down;
		BTNode<K, T> *s = p->ar[n + 1].down;
		Item<K, T> m = s->ar[0];
		removeB(s, 0);
		insertB(r, r->n, m);
		p->ar[n + 1].key = s->ar[0].key;
		
	}
	void correct_filling(BTNode<K, T>* p, int n) {
		if (n > 0) {
			if (p->ar[n - 1].down->n > N / 2) pass_forward(p, n - 1);
			else join(p, n - 1);
		}
		else if (n < p->n - 1) {
			if (p->ar[n + 1].down->n > N / 2) pass_backward(p, n);
			else join(p, n);
		}
	}
	void removeR(BTNode<K, T>* p, K k, int h, bool& corr_key, bool& corr_fill) {
		if (h == 1) {
			for (int i = 0; i < p->n; i++) {
				if (p->ar[i].key == k) {
					removeB(p, i);
					corr_key = i == 0;
					corr_fill = p->n < N / 2;
					return;
				}
			}
		}
		if (k < p->ar[0].key) return;
		int t = p->n - 1;
		for (int i = 1; i < p->n; i++) {
			if (p->ar[i].key > k) {
				t = i - 1;
				break;
			}
		}
		removeR(p->ar[t].down, k, h - 1, corr_key, corr_fill);
		if (corr_key) p->ar[t].key = p->ar[t].down->ar[0].key;
		if (corr_fill) correct_filling(p, t);
		corr_key = t == 0;
		corr_fill = p->n < N / 2;
	}
	void remove(K k) {
		bool res_k = false, res_f = false;
		removeR(root, k, height, res_k, res_f);
		if (root->n == 1 and height > 1) {
			BTNode<K, T> *del = root;
			root = root->ar[0].down;
			delete del;
			height--;
		}
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
	int k;
	cin >> k;
	while (k != -1) {
		t.remove(k);
		t.print();
		cin >> k;
	}
	return EXIT_SUCCESS;
}
