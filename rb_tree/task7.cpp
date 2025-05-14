#include <iostream>
#include <vector>
using namespace std;

struct Interval {
    int low, high;
    Interval(int l, int h) : low(l), high(h) {}
};

struct Node {
    Interval interval;
    int maxHigh;
    bool isRed;
    Node *left, *right;

    Node(Interval i)
        : interval(i), maxHigh(i.high), isRed(true), left(nullptr), right(nullptr) {}
};

class IntervalTree {
private:
    Node* root;

    // Update maxHigh after insert or changes
    void updateMax(Node* node) {
        if (!node) return;
        node->maxHigh = node->interval.high;
        if (node->left && node->left->maxHigh > node->maxHigh)
            node->maxHigh = node->left->maxHigh;
        if (node->right && node->right->maxHigh > node->maxHigh)
            node->maxHigh = node->right->maxHigh;
    }

    // Check if two intervals overlap
    bool isOverlap(Interval a, Interval b) {
        return a.low <= b.high && b.low <= a.high;
    }

    // Search for all overlapping intervals
    void search(Node* node, Interval q, vector<Interval>& result) {
        if (!node) return;

        if (isOverlap(node->interval, q)) {
            result.push_back(node->interval);
        }

        if (node->left && node->left->maxHigh >= q.low) {
            search(node->left, q, result);
        }

        if (node->right && node->interval.low <= q.high) {
            search(node->right, q, result);
        }
    }

public:
    IntervalTree() : root(nullptr) {}

    void setRoot(Node* r) {
        root = r;
        updateMaxRecursively(root);
    }

    // Helper to fix maxHigh for entire tree
    void updateMaxRecursively(Node* node) {
        if (!node) return;
        updateMaxRecursively(node->left);
        updateMaxRecursively(node->right);
        updateMax(node);
    }

    // Find all intervals overlapping with query
    vector<Interval> findOverlaps(Interval query) {
        vector<Interval> result;
        search(root, query, result);
        return result;
    }
};

// Helper to print intervals
void printIntervals(const vector<Interval>& intervals) {
    for (const auto& iv : intervals)
        cout << "[" << iv.low << ", " << iv.high << "] ";
    cout << endl;
}

int main() {
    IntervalTree tree;

    // Manually create tree
    Node* root = new Node(Interval(15, 20));
    root->isRed = false;

    root->left = new Node(Interval(10, 30));
    root->left->isRed = true;

    root->right = new Node(Interval(17, 19));
    root->right->isRed = true;

    root->left->left = new Node(Interval(5, 20));
    root->left->left->isRed = false;

    root->left->right = new Node(Interval(12, 15));
    root->left->right->isRed = false;

    root->right->right = new Node(Interval(30, 40));
    root->right->right->isRed = false;

    tree.setRoot(root);

    Interval query(14, 16);
    vector<Interval> result = tree.findOverlaps(query);

    cout << "Overlapping intervals with [14, 16]: ";
    printIntervals(result);

    return 0;
}

