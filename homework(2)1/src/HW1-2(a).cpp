#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, int key) {
        if (node == nullptr) {
            return new Node(key);
        }

        if (key < node->key) {
            node->left = insert(node->left, key);
        }
        else if (key > node->key) {
            node->right = insert(node->right, key);
        }

        return node;
    }

    int height(Node* node) const {
        if (node == nullptr) {
            return 0;
        }

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }

    void clear(Node* node) {
        if (node == nullptr) {
            return;
        }

        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        clear(root);
    }

    void insert(int key) {
        root = insert(root, key);
    }

    int height() const {
        return height(root);
    }
};

int main() {
    srand((unsigned)time(0));

    int testN[] = {100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    int size = sizeof(testN) / sizeof(testN[0]);

    cout << left << setw(10) << "n"
         << setw(10) << "Height"
         << setw(15) << "log2(n)"
         << setw(20) << "Height/log2(n)" << endl;

    for (int i = 0; i < size; i++) {
        int n = testN[i];
        BST tree;

        for (int j = 0; j < n; j++) {
            int value = rand();
            tree.insert(value);
        }

        int h = tree.height();
        double logn = log2((double)n);
        double ratio = h / logn;

        cout << left << setw(10) << n
             << setw(10) << h
             << setw(15) << fixed << setprecision(4) << logn
             << setw(20) << fixed << setprecision(4) << ratio << endl;
    }

    return 0;
}
