#include <iostream>
using namespace std;

struct Node {
    int key;
    bool isRed;  // true = RED, false = BLACK
    Node *left, *right;
    int size;    // stores size of subtree rooted at this node

    Node(int k) : key(k), isRed(true), left(nullptr), right(nullptr), size(1) {}
};

class RBTree {
private:
    Node* root;

    // Update the size of the node after insertion or deletion
    void updateSize(Node* node) {
        if (node)
            node->size = 1 + (node->left ? node->left->size : 0) + (node->right ? node->right->size : 0);
    }

    // Helper function to count nodes within the range [low, high]
    int countInRange(Node* node, int low, int high) {
        if (!node) return 0;

        // If current node is outside the range, no need to visit this subtree
        if (node->key < low) return countInRange(node->right, low, high);
        if (node->key > high) return countInRange(node->left, low, high);

        // Current node is in the range, count left, right, and itself
        return 1 + countInRange(node->left, low, high) + countInRange(node->right, low, high);
    }

public:
    RBTree() : root(nullptr) {}

    void setRoot(Node* r) { root = r; }

    // Public function to count nodes within a given range
    int countRange(int low, int high) {
        return countInRange(root, low, high);
    }
};

int main() {
    RBTree tree;

    Node* root = new Node(10);
    root->isRed = false; // BLACK
    root->left = new Node(5);
    root->right = new Node(19);
    root->left->isRed = true;  // RED
    root->right->isRed = true; // RED
    tree.setRoot(root);

    // Count nodes in range [5, 15]
    cout << "Count in range [5, 15]: " << tree.countRange(5, 15) << endl;

    return 0;
}
