#include <iostream>
using namespace std;

// Tree Node
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Binary Search Tree Class
class BST {
private:
    TreeNode* root;

    // Helper function for insertion
    TreeNode* insert(TreeNode* node, int value) {
        if (node == nullptr) return new TreeNode(value);

        if (value < node->value)
            node->left = insert(node->left, value);
        else if (value > node->value)
            node->right = insert(node->right, value);

        return node;
    }

    // Helper function for searching
    bool search(TreeNode* node, int value) {
        if (node == nullptr) return false;

        if (node->value == value) return true;
        if (value < node->value) return search(node->left, value);
        return search(node->right, value);
    }

    // Helper function for in-order traversal
    void inOrderTraversal(TreeNode* node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            cout << node->value << " ";
            inOrderTraversal(node->right);
        }
    }

public:
    BST() : root(nullptr) {}

    // Insert a value
    void insert(int value) {
        root = insert(root, value);
    }

    // Search for a value
    bool search(int value) {
        return search(root, value);
    }

    // Display the tree (in-order traversal)
    void display() {
        inOrderTraversal(root);
        cout << endl;
    }
};

// Main Function
int main() {
    BST tree;
    int choice, value;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Display\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            tree.insert(value);
            break;
        case 2:
            cout << "Enter value to search: ";
            cin >> value;
            if (tree.search(value))
                cout << "Value found in the tree.\n";
            else
                cout << "Value not found in the tree.\n";
            break;
        case 3:
            cout << "Tree (In-Order Traversal): ";
            tree.display();
            break;
        case 4:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
