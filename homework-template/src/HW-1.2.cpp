#include <iostream>
#include <vector>
#include <string>
using namespace std;

void generatePowerset(vector<string>& set, int index, vector<string> current, vector<vector<string>>& result) {
    if (index == set.size()) {
        result.push_back(current);
        return;
    }

    generatePowerset(set, index + 1, current, result);

    current.push_back(set[index]);
    generatePowerset(set, index + 1, current, result);
}

int main() {
    int n;
    cout << "請輸入集合元素個數 n: ";
    cin >> n;

    vector<string> set(n);
    cout << "請輸入集合元素（以空白分隔）: ";
    for (int i = 0; i < n; i++) cin >> set[i];

    vector<vector<string>> result;
    vector<string> current;

    generatePowerset(set, 0, current, result);

    cout << "\nPowerset(S) = {" << endl;
    for (auto subset : result) {
        cout << "  { ";
        for (auto elem : subset) cout << elem << " ";
        cout << "}" << endl;
    }
    cout << "}" << endl;

    return 0;
}

