#include <iostream>
using namespace std;

unsigned long long Ackermann(unsigned int m, unsigned int n) {
    if (m == 0) {
        // 當 m = 0 時，回傳 n + 1
        return n + 1;
    } 
    else if (n == 0) {
        // 當 n = 0 時，呼叫 A(m - 1, 1)
        return Ackermann(m - 1, 1);
    } 
    else {
        // 一般情況，呼叫 A(m - 1, A(m, n - 1))
        // 先計算內層 A(m, n - 1)，再把結果代入 A(m - 1, ...)
        return Ackermann(m - 1, Ackermann(m, n - 1));
    }
}

int main() {
    unsigned int m, n;

    cout << "請輸入 m 和 n: ";
    cin >> m >> n;

    // 呼叫遞迴版本 Ackermann 函數
    cout << "Ackermann(" << m << ", " << n << ") = " << Ackermann(m, n) << endl;

    return 0;
}

