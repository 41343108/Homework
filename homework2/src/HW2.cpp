#include<iostream>
using namespace std;

class Polynomial;

class Term {
	friend Polynomial;
	friend ostream& operator<<(ostream& output, const Polynomial& Poly);
private:
	int exp;
	float coef;
};

class Polynomial {
private:
    Term* termArray;
    int capacity;
    int terms;

    void reserve(int need) {
        if (need <= capacity) return;
        int newcap = max(capacity * 2, max(2, need));
        Term* na = new Term[newcap];
        for (int i = 0; i < terms; ++i) na[i] = termArray[i];
        delete[] termArray;
        termArray = na;
        capacity = newcap;
    }

public:
    Polynomial() : termArray(new Term[2]), capacity(2), terms(0) {}
    ~Polynomial() { delete[] termArray; }

    Polynomial(const Polynomial& rhs)
        : termArray(new Term[rhs.capacity]), capacity(rhs.capacity), terms(rhs.terms) {
        for (int i = 0; i < terms; ++i) termArray[i] = rhs.termArray[i];
    }

    Polynomial& operator=(const Polynomial& rhs) {
        if (this == &rhs) return *this;
        Term* na = new Term[rhs.capacity];
        for (int i = 0; i < rhs.terms; ++i) na[i] = rhs.termArray[i];
        delete[] termArray;
        termArray = na;
        capacity = rhs.capacity;
        terms = rhs.terms;
        return *this;
    }

    Polynomial(Polynomial&& rhs) noexcept
        : termArray(rhs.termArray), capacity(rhs.capacity), terms(rhs.terms) {
        rhs.termArray = nullptr; rhs.capacity = rhs.terms = 0;
    }
    Polynomial& operator=(Polynomial&& rhs) noexcept {
        if (this == &rhs) return *this;
        delete[] termArray;
        termArray = rhs.termArray; capacity = rhs.capacity; terms = rhs.terms;
        rhs.termArray = nullptr; rhs.capacity = rhs.terms = 0;
        return *this;
    }


    Polynomial Add(const Polynomial& b) const; 
    Polynomial Mult(const Polynomial& b) const; 
    float Eval(float x) const;                  

    void newTerm(const float newcoef, const int newexp) {
        reserve(terms + 1);
        termArray[terms].coef = newcoef;
        termArray[terms].exp = newexp;
        ++terms;
    }

    friend istream& operator>>(istream& input, Polynomial& Poly);
    friend ostream& operator<<(ostream& output, const Polynomial& Poly);
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

Polynomial Polynomial::Add(const Polynomial& b) const {
    Polynomial c;
    int aPos = 0, bPos = 0;
    while ((aPos < terms) && (bPos < b.terms)) {
        if (termArray[aPos].exp == b.termArray[bPos].exp) {
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if (t) c.newTerm(t, termArray[aPos].exp);
            ++aPos; ++bPos;
        }
        else if (termArray[aPos].exp < b.termArray[bPos].exp) { 
            c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            ++bPos;
        }
        else {
            c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
            ++aPos;
        }
    }
    for (; aPos < terms; ++aPos) c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
    for (; bPos < b.terms; ++bPos) c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
    return c; 
}

int main() {
	Polynomial polyA, polyB, result;

	cin >> polyA >> polyB;
	result = polyA.Add(polyB);

	cout << result << endl;

	return 0;
}
