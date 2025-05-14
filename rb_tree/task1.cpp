// Task 1: Height of Red-Black Tree
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

    int height(Node* node) {
        if (!node) return -1;
        return 1 + max(height(node->left), height(node->right));
    }

public:
    RBTree() : root(nullptr) {}

    void setRoot(Node* r) { root = r; }

    int getHeight() { return height(root); }
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

    cout << "Height: " << tree.getHeight() << endl;
    return 0;
}
