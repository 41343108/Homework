#include <iostream>
using namespace std;

unsigned long long Ackermann(unsigned int m, unsigned int n) {
    if (m == 0) {
        return n + 1;
    } 
    else if (n == 0) {
        return Ackermann(m - 1, 1);
    } 
    else {
        return Ackermann(m - 1, Ackermann(m, n - 1));
    }
}

int main() {
    unsigned int m, n;

    cout << "請輸入 m 和 n: ";
    cin >> m >> n;

    cout << "Ackermann(" << m << ", " << n << ") = " << Ackermann(m, n) << endl;

    return 0;
}

