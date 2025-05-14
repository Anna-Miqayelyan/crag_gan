#include <iostream>
#include <stack>
using namespace std;

struct Node {
    int key;
    bool isRed;  // true = RED, false = BLACK
    Node *left, *right;

    Node(int k) : key(k), isRed(true), left(nullptr), right(nullptr) {}
};

class RBTree {
private:
    Node* root;

   
    void inorderHelper(Node* node) {
        if (node) {
            inorderHelper(node->left);   
            cout << node->key << " ";      
            inorderHelper(node->right);   
        }
    }

public:
    RBTree() : root(nullptr) {}

    void setRoot(Node* r) { root = r; }

    void inorderTraversal() {
        inorderHelper(root);
        cout << endl;
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

    // In-order traversal using helper function
    cout << "In-order traversal: ";
    tree.inorderTraversal();

    
    cout << endl;

    return 0;
}
