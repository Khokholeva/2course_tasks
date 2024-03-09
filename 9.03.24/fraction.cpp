#include <iostream>
#include <cstdlib>
#include <initializer_list>
using namespace std;

struct Fraction
{
	int num, den;
	Fraction(int a = 0, int b = 1): num(a), den(b) {
		if (den < 0) {
			num /= -1;
			den /= -1;
		}
		int x = 2;
		while (abs(num) >= x and den >= x) {
			while (num % x == 0 and den % x == 0) {
				num /= x;
				den /= x;
			}
			x++;
		}
	}
};

ostream& operator <<(ostream& st, Fraction a) {
	if (a.den == 1) return st << a.num;
	return st << a.num << "/" << a.den;
}

Fraction operator+(Fraction p, Fraction q) {
	Fraction ans(p.num * q.den + p.den * q.num, p.den * q.den);
	return ans;
}
Fraction operator-(Fraction p, Fraction q) {
	Fraction ans(p.num * q.den - p.den * q.num, p.den * q.den);
	return ans;
}
Fraction operator*(Fraction p, Fraction q) {
	Fraction ans(p.num * q.num, p.den * q.den);
	return ans;
}
Fraction operator/(Fraction p, Fraction q) {
	Fraction ans(p.num * q.den, p.den * q.num);
	return ans;
}

bool operator ==(Fraction a, Fraction b) {
	return a.num == b.num and a.den == b.den;
}

bool operator !=(Fraction a, Fraction b) {
	return !(a == b);
}

bool operator >(Fraction a, Fraction b) {
	return a.num * b.den > b.num * a.den;
}

bool operator <(Fraction a, Fraction b) {
	return a.num * b.den < b.num * a.den;
}
bool operator >=(Fraction a, Fraction b) {
	return !(a < b);
}
bool operator <=(Fraction a, Fraction b) {
	return !(a > b);
}

int main()
{
	setlocale(LC_ALL, "Russian");

	Fraction f(1, 3);
	Fraction g(5, -3);
	cout << f + g << endl;
	cout << f * 6 << endl;
	cout << boolalpha << (f > g) << endl;
	return EXIT_SUCCESS;
}
