#include <iostream>
#include <vector>
using namespace std;

void powerset(vector<char>& set, vector<char>& subset, int index) {
    if (index == set.size()) {
        
        cout << "{ ";
        for (char c : subset) {
            cout << c << " ";
        }
        cout << "}" << endl;
        return;
    }

    powerset(set, subset, index + 1);

    subset.push_back(set[index]);
    powerset(set, subset, index + 1);

    subset.pop_back();
}

int main() {
    vector<char> S = {'a', 'b', 'c'};
    vector<char> subset;
    cout << "Powerset:" << endl;
    powerset(S, subset, 0);
    return 0;
}
