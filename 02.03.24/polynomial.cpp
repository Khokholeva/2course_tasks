#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Polynomial
{
	int degree;
	double* coeffs;
	Polynomial() : degree(0), coeffs(new double[1] {0}) {}
	Polynomial(int d, double* c) {
		degree = d;
		coeffs = new double[d + 1];
		for (int i = 0; i <= d; i++) {
			coeffs[i] = c[i];
		}
	}
	~Polynomial() {
		delete[] coeffs;
	}
	double value(double x) {
		double ans = 0;
		double x_pow = 1;
		for (int i = 0; i <= degree; i++) {
			ans += x_pow * coeffs[i];
			x_pow *= x;
		}
		return ans;
	}

	double& operator[] (int d) {
		static double c = -1;
		if (0 <= d && d <= degree) return coeffs[d];
		else cout << "Выход за пределы массива" << endl;
		return c;
	}

	Polynomial& operator= (const Polynomial & a) {
	if(this == &a) { // проверка на самоприсваивание
		return *this;
	}
	degree = a.degree;
	delete[] coeffs;
	coeffs = new double[degree + 1];
	for (int i = 0; i <= degree; i++) {
		coeffs[i] = a.coeffs[i];
	}
	return *this;
	}
};

Polynomial operator+(Polynomial& a, Polynomial& b) {
	int d_c = a.degree > b.degree ? a.degree : b.degree;
	double *coef_c;
	coef_c = new double[d_c+1];
	double temp;
	for (int i = 0; i <= d_c; i++) {
		temp = 0;
		if (i <= a.degree) temp += a[i];
		if (i <= b.degree) temp += b[i];
		coef_c[i] = temp;
	}
	Polynomial c(d_c, coef_c);
	return c;
}

Polynomial operator-(Polynomial& a, Polynomial& b) {
	int d_c = a.degree > b.degree ? a.degree : b.degree;
	double* coef_c;
	coef_c = new double[d_c + 1];
	double temp;
	for (int i = 0; i <= d_c; i++) {
		temp = 0;
		if (i <= a.degree) temp += a[i];
		if (i <= b.degree) temp -= b[i];
		coef_c[i] = temp;
	}
	Polynomial c(d_c, coef_c);
	return c;
}

Polynomial operator*(Polynomial& a, Polynomial& b) {
	int d_c = a.degree + b.degree;
	double* coef_c;
	coef_c = new double[d_c + 1] {};
	for (int i = 0; i <= a.degree; i++) {
		for (int j = 0; j <= b.degree; j++) {
			coef_c[i + j] += a[i] * b[j];
		}
	}
	Polynomial c(d_c, coef_c);
	return c;
}

ostream& operator << (ostream& st, Polynomial &a)
{
	int t = 0;
	while (t <= a.degree and a[t] == 0) t++;
	if (t > a.degree) return st << 0;
	for (int i = a.degree; i > t; i--) {
		if (i == 1 and a[i] != 0) st << a[i] << "*x" << " + ";
		else if (a[i] != 0) st << a[i] << "*x^" << i << " + ";

	}
	if (t > 1) return st << a[t] << "*x^" << t;
	else if (t == 1) return st << a[t] << "*x";
	else return st << a[t];

}

istream& operator >> (istream& st, Polynomial& a)
{
	st >> a.degree;
	a.coeffs = new double[a.degree + 1];
	for (int i = 0; i <= a.degree; i++) {
		st >> a[i];
	}
	return st;
}

Polynomial operator/(Polynomial &a, Polynomial &b) {
	int b_d = b.degree;
	int a_d = a.degree;
	while (b_d >= 0 and b[b_d] == 0) b_d -= 1;
	if (b_d == -1) {
		Polynomial ans(0, { 0 });
		return ans;
	}
	int d = a.degree - b_d;
	double x;
	double* res = new double[d + 1] {0};
	double* temp = new double[a_d + 1];
	for (int i = 0; i <= a_d; i++) {
		temp[i] = a[i];
	}
	for (int i = 0; i <= d; i++) {
		x = temp[a_d - i] / b[b_d];
		res[d - i] = x;
		for (int j = 0; j <= b_d; j++) {
			temp[a_d - j] -= x * b[b_d - j];
			
		}
	}
	Polynomial ans(d, res);
	return ans;
}

Polynomial operator%(Polynomial& a, Polynomial& b) {
	Polynomial c = a / b;
	c = c * b;
	return a - c;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	double p[2]{ 1,1 };
	double q[3]{ 1, 2, 1};
	Polynomial a(1, p);
	Polynomial b(2, q);
	cout << a << " (3) = " << a.value(3) << endl;
	cout << b << " (4) = " << b.value(4) << endl;
	Polynomial add_ab = a+b;
	cout << add_ab << " (2) = " << add_ab.value(2) << endl;
	Polynomial sub_ab = a-b;
	cout << sub_ab << " (5) = " << sub_ab.value(5) << endl;
	Polynomial mult_ab =a*b;
	cout << mult_ab << " (2) = " << mult_ab.value(2) << endl;
	Polynomial c;
	cout << c << " (3) = " << c.value(3) << endl;
	
	b[2] = 2;
	cout << b << " (5) = " << b.value(5) << endl;

	Polynomial x, y;
	cin >> x >> y;
	

	Polynomial div_xy = x / y;
	Polynomial mod_xy = x % y;
	cout << x << " / " << y << " = " << "(" << div_xy << ")*(" << y << ") + " << mod_xy << endl;
	return EXIT_SUCCESS;
}
