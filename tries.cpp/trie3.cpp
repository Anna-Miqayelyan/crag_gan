#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

struct Node {
    unordered_map<char, Node*> next;  // Maps characters to child nodes
    bool isEndOfWord;                 // Marks the end of a word

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

    // Insert a word into the Trie
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

    // Helper function to recursively find the longest and shortest words
    void findLongestAndShortestWords(Node* node, string currentWord, int& maxLen, int& minLen, vector<string>& longestWords, vector<string>& shortestWords) {
        if (node == nullptr) return;

        // If this is the end of a word, check its length
        if (node->isEndOfWord) {
            int len = currentWord.length();
            // Update the longest words
            if (len > maxLen) {
                maxLen = len;
                longestWords = {currentWord};
            } else if (len == maxLen) {
                longestWords.push_back(currentWord);
            }
            // Update the shortest words
            if (len < minLen) {
                minLen = len;
                shortestWords = {currentWord};
            } else if (len == minLen) {
                shortestWords.push_back(currentWord);
            }
        }

        // Recurse for each child node
        for (auto& pair : node->next) {
            findLongestAndShortestWords(pair.second, currentWord + pair.first, maxLen, minLen, longestWords, shortestWords);
        }
    }

    // Function to find longest and shortest words
    void getLongestAndShortestWords(vector<string>& longestWords, vector<string>& shortestWords) {
        int maxLen = 0, minLen = INT_MAX;
        findLongestAndShortestWords(root, "", maxLen, minLen, longestWords, shortestWords);
    }
};

int main() {
    // Initialize the Trie
    Trie trie;

    // Insert words into the Trie
    vector<string> words = {"apple", "bat", "banana", "dog", "cat", "ape"};
    for (const string& word : words) {
        trie.insert(word);
    }

    // Get longest and shortest words
    vector<string> longestWords;
    vector<string> shortestWords;
    trie.getLongestAndShortestWords(longestWords, shortestWords);

    // Output the longest words
    cout << "Longest word(s): ";
    for (const string& word : longestWords) {
        cout << word << " ";
    }
    cout << endl;

    // Output the shortest words
    cout << "Shortest word(s): ";
    for (const string& word : shortestWords) {
        cout << word << " ";
    }
    cout << endl;

    return 0;
}
