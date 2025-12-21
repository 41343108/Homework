#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

class Polynomial {
private:
    struct Node {
        int coef;
        int exp;
        Node* link;
    };

    Node* header;
    static Node* avail;

    static Node* GetNode(int c = 0, int e = 0) {
        Node* p;
        if (avail) {
            p = avail;
            avail = avail->link;
        }
        else {
            p = new Node;
        }
        p->coef = c;
        p->exp = e;
        p->link = nullptr;
        return p;
    }

    static void RetNode(Node* p) {
        if (!p) return;
        p->link = avail;
        avail = p;
    }

    void ClearTerms() {
        Node* cur = header->link;
        while (cur != header) {
            Node* next = cur->link;
            RetNode(cur);
            cur = next;
        }
        header->link = header;
    }

    void CopyFrom(const Polynomial& other) {
        // assume *this is empty (only header)
        Node* tail = header;
        for (Node* p = other.header->link; p != other.header; p = p->link) {
            Node* n = GetNode(p->coef, p->exp);
            tail->link = n;
            tail = n;
        }
        tail->link = header; // close circle
    }

    void AddTerm(int c, int e) {
        if (c == 0) return;

        Node* prev = header;
        Node* cur = header->link;

        // find insertion position (descending by exp)
        while (cur != header && cur->exp > e) {
            prev = cur;
            cur = cur->link;
        }

        // if same exponent, combine
        if (cur != header && cur->exp == e) {
            cur->coef += c;
            if (cur->coef == 0) { // remove node if becomes 0
                prev->link = cur->link;
                RetNode(cur);
            }
            return;
        }

        // insert new node between prev and cur
        Node* n = GetNode(c, e);
        prev->link = n;
        n->link = cur;
    }

    int TermCount() const {
        int cnt = 0;
        for (Node* p = header->link; p != header; p = p->link) cnt++;
        return cnt;
    }

public:

    Polynomial() {
        header = GetNode(0, 0);
        header->link = header; // empty circular list
    }

    Polynomial(const Polynomial& a) {
        header = GetNode(0, 0);
        header->link = header;
        CopyFrom(a);
    }

    Polynomial& operator=(const Polynomial& a) {
        if (this == &a) return *this;
        ClearTerms();
        CopyFrom(a);
        return *this;
    }

    ~Polynomial() {
        ClearTerms();
        RetNode(header);
        header = nullptr;
    }

    Polynomial operator+(const Polynomial& b) const {
        Polynomial r;

        Node* p = this->header->link;
        Node* q = b.header->link;

        while (p != this->header && q != b.header) {
            if (p->exp == q->exp) {
                r.AddTerm(p->coef + q->coef, p->exp);
                p = p->link;
                q = q->link;
            }
            else if (p->exp > q->exp) {
                r.AddTerm(p->coef, p->exp);
                p = p->link;
            }
            else {
                r.AddTerm(q->coef, q->exp);
                q = q->link;
            }
        }
        while (p != this->header) {
            r.AddTerm(p->coef, p->exp);
            p = p->link;
        }
        while (q != b.header) {
            r.AddTerm(q->coef, q->exp);
            q = q->link;
        }

        return r;
    }

    Polynomial operator-(const Polynomial& b) const {
        Polynomial r;

        Node* p = this->header->link;
        Node* q = b.header->link;

        while (p != this->header && q != b.header) {
            if (p->exp == q->exp) {
                r.AddTerm(p->coef - q->coef, p->exp);
                p = p->link;
                q = q->link;
            }
            else if (p->exp > q->exp) {
                r.AddTerm(p->coef, p->exp);
                p = p->link;
            }
            else {
                r.AddTerm(-q->coef, q->exp);
                q = q->link;
            }
        }
        while (p != this->header) {
            r.AddTerm(p->coef, p->exp);
            p = p->link;
        }
        while (q != b.header) {
            r.AddTerm(-q->coef, q->exp);
            q = q->link;
        }

        return r;
    }

    Polynomial operator*(const Polynomial& b) const {
        Polynomial r;

        for (Node* p = this->header->link; p != this->header; p = p->link) {
            for (Node* q = b.header->link; q != b.header; q = q->link) {
                long long coefMul = 1LL * p->coef * q->coef;
                int expSum = p->exp + q->exp;
                // AddTerm expects int coef; if overflow is a concern, you can change coef to long long
                r.AddTerm((int)coefMul, expSum);
            }
        }
        return r;
    }

    float Evaluate(float x) const {
        double sum = 0.0;
        for (Node* p = header->link; p != header; p = p->link) {
            sum += (double)p->coef * pow((double)x, (double)p->exp);
        }
        return (float)sum;
    }

    friend istream& operator>>(istream& is, Polynomial& x) {
        int n;
        if (!(is >> n)) return is;

        x.ClearTerms();

        for (int i = 0; i < n; i++) {
            int c, e;
            is >> c >> e;
            x.AddTerm(c, e);
        }
        return is;
    }

    friend ostream& operator<<(ostream& os, const Polynomial& x) {
        int n = x.TermCount();
        os << n;

        for (Node* p = x.header->link; p != x.header; p = p->link) {
            os << " " << p->coef << " " << p->exp;
        }
        return os;
    }
};

Polynomial::Node* Polynomial::avail = nullptr;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Polynomial A, B;

   
    cout << "A = ";
    cin >> A;

    cout << "B = ";
    cin >> B;

    cout << "\nA (external) = " << A << "\n";
    cout << "B (external) = " << B << "\n";

    Polynomial S = A + B;
    Polynomial D = A - B;
    Polynomial P = A * B;

    cout << "\nA + B = " << S << "\n";
    cout << "A - B = " << D << "\n";
    cout << "A * B = " << P << "\n";

    float x;
    cout << "\nEnter x to evaluate A(x): ";
    cin >> x;
    cout << "A(" << x << ") = " << A.Evaluate(x) << "\n";

    return 0;
}
