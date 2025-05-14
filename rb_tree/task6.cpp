#include <iostream>
using namespace std;

struct Node {
    int key;
    bool isRed;  // true = RED, false = BLACK
    Node *left, *right;
    int size;    // number of nodes in subtree

    Node(int k) : key(k), isRed(true), left(nullptr), right(nullptr), size(1) {}
};

class RBTree {
private:
    Node* root;

    // Update size after insertion or structure change
    void updateSize(Node* node) {
        if (node) {
            node->size = 1;
            if (node->left) node->size += node->left->size;
            if (node->right) node->size += node->right->size;
        }
    }

    // Helper: kth smallest element
    Node* kth(Node* node, int k) {
        if (!node) return nullptr;

        int leftSize = (node->left) ? node->left->size : 0;

        if (k == leftSize + 1)
            return node;
        else if (k <= leftSize)
            return kth(node->left, k);
        else
            return kth(node->right, k - leftSize - 1);
    }

    // Helper: rank of x (number of elements < x)
    int rank(Node* node, int x) {
        if (!node) return 0;

        if (x <= node->key)
            return rank(node->left, x);
        else {
            int leftSize = (node->left) ? node->left->size : 0;
            return 1 + leftSize + rank(node->right, x);
        }
    }

    void fixSizes(Node* node) {
        if (!node) return;
        fixSizes(node->left);
        fixSizes(node->right);
        updateSize(node);
    }

public:
    RBTree() : root(nullptr) {}

    void setRoot(Node* r) {
        root = r;
        fixSizes(root); // Make sure sizes are correct
    }

    // Return k-th smallest key (1-based index)
    int kthSmallest(int k) {
        Node* res = kth(root, k);
        return res ? res->key : -1;
    }

    // Return number of elements strictly less than x
    int getRank(int x) {
        return rank(root, x);
    }
};

int main() {
    RBTree tree;

    // Sample tree manually constructed
    Node* root = new Node(10);
    root->isRed = false;
    root->left = new Node(5);
    root->right = new Node(15);
    root->left->isRed = true;
    root->right->isRed = true;

    root->left->left = new Node(3);
    root->left->left->isRed = false;

    root->left->right = new Node(7);
    root->left->right->isRed = false;

    tree.setRoot(root);

    // Example usages
    cout << "1st smallest: " << tree.kthSmallest(1) << endl; // 3
    cout << "3rd smallest: " << tree.kthSmallest(3) << endl; // 7
    cout << "Rank of 10: " << tree.getRank(10) << endl;      // 4 (3, 5, 7, < 10)

    return 0;
}
