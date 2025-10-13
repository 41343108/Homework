#include <iostream>
#include <stack>
using namespace std;

unsigned long long AckermannNonRecursive(unsigned int m, unsigned int n) {
    stack<unsigned int> s;
    s.push(m);

    while (!s.empty()) {
        m = s.top();
        s.pop();

        if (m == 0) {
            n = n + 1;
        } 
        else if (n == 0) {
            s.push(m - 1);
            n = 1;
        } 
        else {
            s.push(m - 1);
            s.push(m);
            n = n - 1;
        }
    }
    return n;
}

int main() {
    unsigned int m, n;

    cout << "請輸入 m 和 n: ";
    cin >> m >> n;

    cout << "Ackermann(" << m << ", " << n << ") = " << AckermannNonRecursive(m, n) << endl;

    return 0;
}
