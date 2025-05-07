<<<<<<< HEAD
#include <iostream>
#include <unordered_map>
using namespace std;

struct Node {
    unordered_map<char, Node*> next;
    bool isWord;

    Node() {
        isWord = false;
    }
};

class Trie {
    Node* root;

public:
    Trie() {
        root = new Node();
    }

    // Insert word
    void insert(const string& word) {
        Node* curr = root;
        for (char ch : word) {
            if (!curr->next[ch])
                curr->next[ch] = new Node();
            curr = curr->next[ch];
        }
        curr->isWord = true;
    }

    // Search word
    bool search(const string& word) {
        Node* curr = root;
        for (char ch : word) {
            if (!curr->next.count(ch))
                return false;
            curr = curr->next[ch];
        }
        return curr->isWord;
    }

    // Delete word (simple: just unmark as word)
    void remove(const string& word) {
        Node* curr = root;
        for (char ch : word) {
            if (!curr->next.count(ch))
                return; // word doesn't exist
            curr = curr->next[ch];
        }
        curr->isWord = false; // unmark it
    }
};

int main() {
    Trie trie;
    trie.insert("cat");
    trie.insert("dog");

    cout << "Search cat: " << trie.search("cat") << endl; // 1
    cout << "Search dog: " << trie.search("dog") << endl; // 1
    cout << "Search cow: " << trie.search("cow") << endl; // 0

    trie.remove("cat");
    cout << "Search cat after delete: " << trie.search("cat") << endl; // 0

    return 0;
}
    
=======
#include <iostream>
#include <unordered_map>
using namespace std;

struct Node {
    unordered_map<char, Node*> next;
    bool isWord;

    Node() {
        isWord = false;
    }
};

class Trie {
    Node* root;

public:
    Trie() {
        root = new Node();
    }

    // Insert word
    void insert(const string& word) {
        Node* curr = root;
        for (char ch : word) {
            if (!curr->next[ch])
                curr->next[ch] = new Node();
            curr = curr->next[ch];
        }
        curr->isWord = true;
    }

    // Search word
    bool search(const string& word) {
        Node* curr = root;
        for (char ch : word) {
            if (!curr->next.count(ch))
                return false;
            curr = curr->next[ch];
        }
        return curr->isWord;
    }

    // Delete word (simple: just unmark as word)
    void remove(const string& word) {
        Node* curr = root;
        for (char ch : word) {
            if (!curr->next.count(ch))
                return; // word doesn't exist
            curr = curr->next[ch];
        }
        curr->isWord = false; // unmark it
    }
};

int main() {
    Trie trie;
    trie.insert("cat");
    trie.insert("dog");

    cout << "Search cat: " << trie.search("cat") << endl; // 1
    cout << "Search dog: " << trie.search("dog") << endl; // 1
    cout << "Search cow: " << trie.search("cow") << endl; // 0

    trie.remove("cat");
    cout << "Search cat after delete: " << trie.search("cat") << endl; // 0

    return 0;
}
    
>>>>>>> 8a78bdbadaf1c8618c059c1ea436e4b3e5c91025
