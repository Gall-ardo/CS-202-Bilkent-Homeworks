#include "AVL_Tree.h"
#include <iostream>
using namespace std;

// Public functions
AVL_Tree::AVL_Tree() {
    root = nullptr;
}

AVL_Tree::AVL_Tree(int *arr, int n) {
    root = nullptr;
    for(int i = 0; i < n; i++) {
        bool inserted = false;
        root = insertHelper(root, arr[i], &inserted);
    }
}

AVL_Tree::~AVL_Tree() {
    clear();
}

bool AVL_Tree::search(int key) {
    return searchHelper(root, key);
}

bool AVL_Tree::isEmpty() {
    return root == nullptr;
}

void AVL_Tree::clear() {
    clearHelper(root);
    root = nullptr;
}

bool AVL_Tree::insert(int key) {
    bool inserted = false;
    root = insertHelper(root, key, &inserted);
    return inserted;
}

bool AVL_Tree::remove(int key) {
    bool removed = false;
    root = removeHelper(root, key, removed);
    return removed;
}

// Private functions
int AVL_Tree::getHeight(AVL_Node *node) {
    if(node == nullptr) {
        return 0;
    }
    return node->height;
}

int AVL_Tree::getBalance(AVL_Node *node) {
    if(node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// Returns the new root
AVL_Node * AVL_Tree::rightRotate(AVL_Node *y) {
    AVL_Node* leftChild = y->left;
    y->left = leftChild->right;
    leftChild->right = y;

    // update heights
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    leftChild->height = 1 + max(getHeight(leftChild->left), getHeight(leftChild->right));
    return leftChild;
}

AVL_Node * AVL_Tree::leftRotate(AVL_Node *x) {
    AVL_Node* rightNode = x->right;
    x->right = rightNode->left;
    rightNode->left = x;

    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    rightNode->height = 1 + max(getHeight(rightNode->left), getHeight(rightNode->right));
    return rightNode;
}

AVL_Node* AVL_Tree::minValueNode(AVL_Node *node) {
    AVL_Node* current = node;
    while(current->left != nullptr) {
        current = current->left;
    }
    return current;
}

bool AVL_Tree::searchHelper(AVL_Node *node, int key) {
    if(node == nullptr) {
        return false;
    }
    if(node->key == key) {
        return true;
    }
    if(key < node->key) {
        return searchHelper(node->left, key);
    } else {
        return searchHelper(node->right, key);
    }
}

void AVL_Tree::clearHelper(AVL_Node *node) {
    if(node == nullptr) {
        return;
    }
    clearHelper(node->left);
    clearHelper(node->right);
    delete node;
}

AVL_Node* AVL_Tree::insertHelper(AVL_Node* node, int key, bool* inserted) {
    if(node == nullptr) {
        *inserted = true;
        return new AVL_Node(key);
    }

    if(key < node->key) {
        node->left = insertHelper(node->left, key, inserted);
    }
    else {
        // Key is >= node->key, always go right for duplicates
        node->right = insertHelper(node->right, key, inserted);
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    // Left Left Case
    if(balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    // Right Right Case
    if(balance < -1 && key >= node->right->key) {
        return leftRotate(node);
    }

    // Left Right Case
    if(balance > 1 && key >= node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if(balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

AVL_Node* AVL_Tree::removeHelper(AVL_Node* node, int key, bool& removed) {
    if(node == nullptr) {
        removed = false;
        return nullptr;
    }

    if(key < node->key) {
        node->left = removeHelper(node->left, key, removed);
    }
    else if(key > node->key) {
        node->right = removeHelper(node->right, key, removed);
    }
    else {  // key == node->key
        // Check for duplicates in left subtree first
        bool hasLeftDuplicate = false;
        AVL_Node* temp = node->left;
        while(temp) {
            if(temp->key == key) {
                hasLeftDuplicate = true;
                break;
            }
            temp = temp->right;
        }

        if(hasLeftDuplicate) {
            node->left = removeHelper(node->left, key, removed);
        }
        else {
            removed = true;
            // Node with only one child or no child
            if(node->left == nullptr) {
                AVL_Node* temp = node->right;
                delete node;
                return temp;
            }
            else if(node->right == nullptr) {
                AVL_Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children
            AVL_Node* temp = minValueNode(node->right);
            node->key = temp->key;
            node->right = removeHelper(node->right, temp->key, removed);
        }
    }

    if(node == nullptr) {
        return nullptr;
    }

    // Update height
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Calculate balance factor
    int balance = getBalance(node);

    // Left Left Case
    if(balance > 1 && getBalance(node->left) >= 0) {
        return rightRotate(node);
    }

    // Left Right Case
    if(balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Right Case
    if(balance < -1 && getBalance(node->right) <= 0) {
        return leftRotate(node);
    }

    // Right Left Case
    if(balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

int AVL_Tree::findMax() {
    if(isEmpty()) {
        return -1;
    }
    AVL_Node* current = root;
    while(current->right != nullptr) {
        current = current->right;
    }
    return current->key;
}

int AVL_Tree::findMin() {
    if(isEmpty()) {
        return -1;
    }

    AVL_Node* current = root;
    while(current->left != nullptr) {
        current = current->left;
    }
    return current->key;
}

int AVL_Tree::findPredecessor(int key) {
    AVL_Node* current = root;
    AVL_Node* predecessor = nullptr;

    while(current != nullptr) {
        if(key <= current->key) {
            current = current->left;
        } else {
            predecessor = current;
            current = current->right;
        }
    }

    if(predecessor == nullptr) {
        return -1;
    }
    return predecessor->key;
}

int AVL_Tree::findSuccessor(int key) {
    AVL_Node* current = root;
    AVL_Node* successor = nullptr;

    while(current != nullptr) {
        if(key < current->key) {
            successor = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if(successor == nullptr) {
        return -1;
    }
    return successor->key;
}

void AVL_Tree::levelOrder() {
    if(isEmpty()) {
        return;
    }

    Queue<AVL_Node*> q;
    q.push(root);

    while(!q.isEmpty()) {
        AVL_Node* current = q.getFront();
        q.pop();

        cout << current->key << " ";

        if(current->left != nullptr) {
            q.push(current->left);
        }
        if(current->right != nullptr) {
            q.push(current->right);
        }
    }


}