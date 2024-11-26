#include <iostream>
#include <map>
#include <vector>
using namespace std;

// Suffix Tree Node
struct SuffixTreeNode {
    map<char, SuffixTreeNode*> children; // Child nodes
    vector<int> indexes;                // Stores suffix starting indexes

    // Insert a suffix into the tree
    void insertSuffix(const string& suffix, int index) {
        indexes.push_back(index);
        if (!suffix.empty()) {
            char firstChar = suffix[0];
            if (children[firstChar] == nullptr) {
                children[firstChar] = new SuffixTreeNode();
            }
            children[firstChar]->insertSuffix(suffix.substr(1), index);
        }
    }

    // Search for a pattern in the tree
    vector<int> search(const string& pattern) {
        if (pattern.empty()) return indexes;
        char firstChar = pattern[0];
        if (children[firstChar]) {
            return children[firstChar]->search(pattern.substr(1));
        }
        return {}; // Pattern not found
    }
};

// Suffix Tree class
class SuffixTree {
    SuffixTreeNode* root;

public:
    SuffixTree(const string& text) {
        root = new SuffixTreeNode();
        for (int i = 0; i < text.length(); i++) {
            root->insertSuffix(text.substr(i), i);
        }
    }

    vector<int> search(const string& pattern) {
        return root->search(pattern);
    }
};

// Main Function
int main() {
    string text, pattern;
    cout << "Enter the text: ";
    cin >> text;

    SuffixTree tree(text);

    cout << "Enter the pattern to search: ";
    cin >> pattern;

    vector<int> result = tree.search(pattern);
    if (result.empty()) {
        cout << "Pattern not found.\n";
    } else {
        cout << "Pattern found at indexes: ";
        for (int idx : result) cout << idx << " ";
        cout << endl;
    }

    return 0;
}
