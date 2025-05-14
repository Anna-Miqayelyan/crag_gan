// Task 2: Red-Black Tree Validity Check
#include <iostream>
using namespace std;

struct Node {
    int key;
    bool isRed; // true = RED, false = BLACK
    Node *left, *right;

    Node(int k) : key(k), isRed(true), left(nullptr), right(nullptr) {}
};

class RBTree {
private:
    Node* root;

    bool isValid(Node* node, int& blackHeight, bool parentRed) {
        if (!node) {
            blackHeight = 1;
            return true;
        }

        if (parentRed && node->isRed)
            return false; // no two red nodes in a row

        int leftBlackHeight = 0, rightBlackHeight = 0;

        if (!isValid(node->left, leftBlackHeight, node->isRed)) return false;
        if (!isValid(node->right, rightBlackHeight, node->isRed)) return false;

        if (leftBlackHeight != rightBlackHeight)
            return false; // black height mismatch

        blackHeight = leftBlackHeight + (node->isRed ? 0 : 1);
        return true;
    }

public:
    RBTree() : root(nullptr) {}

    void setRoot(Node* r) { root = r; }

    bool isValidRBTree() {
        if (!root) return true;
        if (root->isRed) return false; // root must be black

        int bh = 0;
        return isValid(root, bh, false);
    }
};

int main() {
    RBTree tree;
    Node* root = new Node(10);
    root->isRed = false; // BLACK
    root->left = new Node(5);
    root->right = new Node(15);
    root->left->isRed = true;  // RED
    root->right->isRed = true; // RED
    tree.setRoot(root);

    cout << (tree.isValidRBTree() ? "Valid" : "Invalid") << endl;
    return 0;
}
