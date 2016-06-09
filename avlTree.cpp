#include <iostream>

using namespace std;

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;
    Node(int k) {
        key = k;
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
    Node* insertNode(Node* node, int newKey);
    void printNode(Node* node);
    void deleteAll(Node* node);
    public:
        AVLTree();
        ~AVLTree();
        void insert(int key);
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

Node* AVLTree::insertNode(Node* node, int newKey) {
    if(!node) return new Node(newKey);
    if(newKey < node->key)
        node->left = insertNode(node->left, newKey);
    else
        node->right = insertNode(node->right, newKey);
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

void AVLTree::insert(int newKey) {
    root = insertNode(root, newKey);
}

void AVLTree::print() {
    printNode(root);
}

int main() {
    AVLTree tree;
    tree.insert(7);
    tree.insert(6);
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);
    tree.print();
    return 0;
}
