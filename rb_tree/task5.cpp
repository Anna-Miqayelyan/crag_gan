#include <iostream>
using namespace std;

struct Node {
    int key;
    bool isRed;  // true = RED, false = BLACK
    Node *left, *right;
    int size;    // size of the subtree rooted at this node
    int sum;     // sum of all values in the subtree rooted at this node

    Node(int k) : key(k), isRed(true), left(nullptr), right(nullptr), size(1), sum(k) {}
};

class RBTree {
private:
    Node* root;

    // Helper function to update size and sum of the node
    void updateSizeAndSum(Node* node) {
        if (node) {
            node->size = 1 + (node->left ? node->left->size : 0) + (node->right ? node->right->size : 0);
            node->sum = node->key + (node->left ? node->left->sum : 0) + (node->right ? node->right->sum : 0);
        }
    }

    // Helper function to count nodes within the range [low, high]
    int countInRange(Node* node, int low, int high) {
        if (!node) return 0;

        // If current node is outside the range, skip the subtree
        if (node->key < low) return countInRange(node->right, low, high);
        if (node->key > high) return countInRange(node->left, low, high);

        // Node is within range, count left, right, and itself
        return 1 + countInRange(node->left, low, high) + countInRange(node->right, low, high);
    }

    // Helper function to calculate the sum of nodes within the range [low, high]
    int sumInRange(Node* node, int low, int high) {
        if (!node) return 0;

        // If current node is outside the range, skip the subtree
        if (node->key < low) return sumInRange(node->right, low, high);
        if (node->key > high) return sumInRange(node->left, low, high);

        // Node is within range, sum left, right, and itself
        return node->key + sumInRange(node->left, low, high) + sumInRange(node->right, low, high);
    }

public:
    RBTree() : root(nullptr) {}

    void setRoot(Node* r) { root = r; }

    // Public function to count nodes within a given range
    int countRange(int low, int high) {
        return countInRange(root, low, high);
    }

    // Public function to calculate the sum of nodes within a given range
    int sumRange(int low, int high) {
        return sumInRange(root, low, high);
    }
};

int main() {
    RBTree tree;

    // Creating a sample tree
    Node* root = new Node(10);
    root->isRed = false; // BLACK
    root->left = new Node(5);
    root->right = new Node(15);
    root->left->isRed = true;  // RED
    root->right->isRed = true; 
    tree.setRoot(root);


    tree.countRange(5, 15);  

    cout << "Count in range [5, 15]: " << tree.countRange(5, 15) << endl;

    cout << "Sum in range [5, 15]: " << tree.sumRange(5, 15) << endl;

    return 0;
}
