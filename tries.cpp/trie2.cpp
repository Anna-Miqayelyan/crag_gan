#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

struct Node {
    unordered_map<char, Node*> next;  // Maps characters to child nodes
    bool isEndOfWord;                 

    Node() {
        isEndOfWord = false;
    }
};

class Trie {
    Node* root;

public:
    Trie() {
        root = new Node();
    }


    void insert(const string& word) {
        Node* curr = root;
        for (char ch : word) {
            if (!curr->next[ch]) {
                curr->next[ch] = new Node();
            }
            curr = curr->next[ch];
        }
        curr->isEndOfWord = true;
    }

    
    bool startsWith(const string& prefix) {
        Node* curr = root;
        for (char ch : prefix) {
            if (!curr->next.count(ch)) {
                return false;  
            }
            curr = curr->next[ch];
        }
        return true;  
    }
};

int main() {
  
    Trie trie;

  
    vector<string> words = {"apple", "app", "banana", "bat", "ball"};

    for (const string& word : words) {
        trie.insert(word);
    }

   
    vector<string> queries = {"app", "bat", "ball", "cat"};

 
    for (const string& prefix : queries) {
        if (trie.startsWith(prefix)) {
            cout << "exists  \"" << prefix << "\"." << endl;
        } else {
            cout << "do not exists \"" << prefix << "\"." << endl;
        }
    }

    return 0;
}
