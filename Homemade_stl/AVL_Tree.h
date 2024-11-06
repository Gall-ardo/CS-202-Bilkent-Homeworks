#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "AVL_Node.h"
#include "queue.h"

class AVL_Tree {
private:
    AVL_Node* root;

    // Helper functions
    int getHeight(AVL_Node* node);
    int getBalance(AVL_Node* node);
    AVL_Node* rightRotate(AVL_Node* y);
    AVL_Node* leftRotate(AVL_Node* x);
    AVL_Node* minValueNode(AVL_Node* node);

    // Recursive helper functions
    void clearHelper(AVL_Node* node);
    bool searchHelper(AVL_Node* node, int key);
    AVL_Node* insertHelper(AVL_Node* node, int key, bool* inserted);
    AVL_Node* removeHelper(AVL_Node *node, int key, bool &removed);


public:
    AVL_Tree();
    AVL_Tree(int* arr, int n);
    ~AVL_Tree();

    bool insert(int key);
    bool remove(int key);
    bool search(int key);
    bool isEmpty();
    void clear();
    int findMax();
    int findMin();
    int findPredecessor(int key);
    int findSuccessor(int key);
    void levelOrder();
};
#endif //AVL_TREE_H
