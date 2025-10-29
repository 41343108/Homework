#include<iostream>
using namespace std;

class Polynomial;

class Term {
	friend Polynomial;
	friend ostream& operator<<(ostream &output, const Polynomial &Poly);
private:
	int exp;
	float coef;
};

class Polynomial {
private:
	Term* termArray;
	int capacity;
	int terms;
public:
	Polynomial() :capacity(2), terms(0) {
		termArray = new Term[capacity];
	}
	~Polynomial() { delete[] termArray; }

	Polynomial Add(Polynomial b);

	Polynomial Mult(Polynomial b);

	float Eval(float x);

	void newTerm(const float newcoef, const int newexp);

	friend istream& operator>>(istream &input, Polynomial &Poly);
	friend ostream& operator<<(ostream &output, const Polynomial &Poly);
};

istream& operator>>(istream& is, Polynomial& poly) {
	float coef;
	int exp, n;
	is >> n;
	while (n--) {
		is >> coef >> exp;
		poly.newTerm(coef, exp);
	}
	return is;
}

ostream& operator<<(ostream& os, const Polynomial& poly) {
	for (int i = 0; i < poly.terms; ++i) {
		if (i > 0)os << " + ";
		os << poly.termArray[i].coef << "X^" << poly.termArray[i].exp;
	}
	return os;
}

Polynomial Polynomial::Add(Polynomial b) {
	Polynomial c;
	int aPos = 0, bPos = 0;
	while((aPos<terms)&&(bPos<b.terms))
		if (termArray[aPos].exp == b.termArray[bPos].exp) {
			float t = termArray[aPos].coef + b.termArray[bPos].coef;
			if (t) c.newTerm(t, termArray[aPos].exp);
			aPos++; bPos++;
		}
		else if (termArray[aPos].exp < b.termArray[bPos].exp) {
			c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
		else {
			c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}

	for (; aPos < terms; aPos++)
		c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
	for (; bPos < b.terms; bPos++)
		c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	return c;
}

int main() {
	Polynomial polyA, polyB, result;

	cin >> polyA >> polyB;
	result = polyA.Add(polyB);

	cout << result << endl;

	return 0;
}
