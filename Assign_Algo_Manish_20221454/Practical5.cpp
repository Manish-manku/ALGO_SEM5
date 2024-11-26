#include <iostream>
#include <vector>
using namespace std;

// B-Tree Node
class BTreeNode {
public:
    vector<int> keys;       // Keys in the node
    vector<BTreeNode*> children; // Child pointers
    bool isLeaf;            // Leaf flag
    int t;                  // Minimum degree

    BTreeNode(int _t, bool _isLeaf) : t(_t), isLeaf(_isLeaf) {}

    // Insert a key into a non-full node
    void insertNonFull(int k);

    // Split a full child
    void splitChild(int i, BTreeNode* y);

    // Traverse the tree
    void traverse();
};

// B-Tree
class BTree {
public:
    BTreeNode* root;
    int t; // Minimum degree

    BTree(int _t) : root(nullptr), t(_t) {}

    // Insert a key
    void insert(int k);

    // Traverse the tree
    void traverse() {
        if (root) root->traverse();
    }
};

// Insert a key into the B-Tree
void BTree::insert(int k) {
    if (!root) {
        root = new BTreeNode(t, true);
        root->keys.push_back(k);
    } else {
        if (root->keys.size() == 2 * t - 1) {
            BTreeNode* newRoot = new BTreeNode(t, false);
            newRoot->children.push_back(root);
            newRoot->splitChild(0, root);
            int i = (newRoot->keys[0] < k) ? 1 : 0;
            newRoot->children[i]->insertNonFull(k);
            root = newRoot;
        } else {
            root->insertNonFull(k);
        }
    }
}

// Insert a key into a non-full node
void BTreeNode::insertNonFull(int k) {
    int i = keys.size() - 1;
    if (isLeaf) {
        keys.push_back(0);
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
    } else {
        while (i >= 0 && keys[i] > k) i--;
        if (children[i + 1]->keys.size() == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            if (keys[i + 1] < k) i++;
        }
        children[i + 1]->insertNonFull(k);
    }
}

// Split a full child
void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(t, y->isLeaf);
    z->keys.assign(y->keys.begin() + t, y->keys.end());
    y->keys.resize(t - 1);
    if (!y->isLeaf) {
        z->children.assign(y->children.begin() + t, y->children.end());
        y->children.resize(t);
    }
    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[t - 1]);
    y->keys.pop_back();
}

// Traverse the tree
void BTreeNode::traverse() {
    int i;
    for (i = 0; i < keys.size(); i++) {
        if (!isLeaf) children[i]->traverse();
        cout << keys[i] << " ";
    }
    if (!isLeaf) children[i]->traverse();
}

// Main function
int main() {
    int t, n;
    cout << "Enter the minimum degree (t) of the B-Tree: ";
    cin >> t;

    BTree tree(t);

    cout << "Enter the number of keys to insert: ";
    cin >> n;

    cout << "Enter the keys: ";
    for (int i = 0; i < n; i++) {
        int key;
        cin >> key;
        tree.insert(key);
    }

    cout << "Traversal of the B-Tree:\n";
    tree.traverse();
    cout << endl;

    return 0;
}
