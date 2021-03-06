#include <iostream>
#include <string>

using namespace std;

struct Node {
    string key, value;
    int height;
    Node* left;
    Node* right;
    Node(string k, string v) {
        key = k;
        value = v;
        left = right = NULL;
        height = 1;
    }
};

class AVLTree {
    Node* root;
    int height(Node* node);
    int balanceFactor(Node* node);
    void updateHeight(Node* node);
    int maxChildHeight(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
    Node* balance(Node* node);
    Node* insertNode(Node* node, string newKey, string newValue);
    string find(Node* node, string key);
    void printNode(Node* node);
    void deleteAll(Node* node);
    public:
        AVLTree();
        ~AVLTree();
        void insert(string key, string value);
        string translate(string key);
        void print();
};

AVLTree::AVLTree() {
    root = NULL;
}

int AVLTree::height(Node* node) {
    return node ? node->height : 0;
}

int AVLTree::balanceFactor(Node* node) {
    return height(node->right) - height(node->left);
}

void AVLTree::updateHeight(Node* node) {
    node->height = maxChildHeight(node) + 1;
}

int AVLTree::maxChildHeight(Node* node) {
    int left = height(node->left);
    int right = height(node->right);
    return left > right ? left : right;
}

Node* AVLTree::rotateRight(Node* node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;
    updateHeight(node);
    updateHeight(leftChild);
    return leftChild;
}

Node* AVLTree::rotateLeft(Node* node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;
    updateHeight(node);
    updateHeight(rightChild);
    return rightChild;
}

Node* AVLTree::balance(Node* node) {
    updateHeight(node);
    if(balanceFactor(node) == 2) {
        if(balanceFactor(node->right) < 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    if(balanceFactor(node) == -2) {
        if(balanceFactor(node->left) > 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    return node;
}

Node* AVLTree::insertNode(Node* node, string newKey, string newValue) {
    if(!node) return new Node(newKey, newValue);
    if(newKey.size() < node->key.size())
        node->left = insertNode(node->left, newKey, newValue);
    else
        node->right = insertNode(node->right, newKey, newValue);
    return balance(node);
}

void AVLTree::printNode(Node* node) {
    if(node) {
        cout << "Node: " << node->key << endl;
        if(node->left) {
            cout << "Left of " << node->key << ":" << endl;
            printNode(node->left);
        }
        if(node->right) {
            cout << "Right of " << node->key << ":" << endl;
            printNode(node->right);
        }
    }
}

void AVLTree::deleteAll(Node* node) {
    if(node->left) {
        deleteAll(node->left);
    }
    if(node->right) {
        deleteAll(node->right);
    }
    delete node;
}

AVLTree::~AVLTree() {
    if(root) deleteAll(root);
}

void AVLTree::insert(string newKey, string newValue) {
    root = insertNode(root, newKey, newValue);
}

string AVLTree::find(Node* node, string key) {
    string result;
    if(node->key == key)
        result = node->value;
    else {
        if(key.size() > node->key.size()) {
            result = find(node->right, key);
        }
        if (key.size() < node->key.size()) {
            result = find(node->left, key);
        }
    }
    return result;
}

string AVLTree::translate(string key) {
    return find(root, key);
}

void AVLTree::print() {
    printNode(root);
}

int main() {
    AVLTree tree;
    string a1 = "grandfather";
    string a2 = "dqdo";
    string b1 = "grandma";
    string b2 = "baba";
    string c1 = "mum";
    string c2 = "mama";
    string d = "alabala";
    tree.insert(a1, a2);
    tree.insert(b1, b2);
    tree.insert(c1, c2);
    tree.print();
    cout << tree.translate(a1) << endl;
    cout << tree.translate(d) << endl;
    return 0;
}
