/**
* Title: Heap and AVL Trees
* Author : Halil Arda Özongun
* ID: 22202709
* Section : 1
* Homework : 2
* Description : This is the header file for the AVL_Node class.
*/

#ifndef AVL_NODE_H
#define AVL_NODE_H

struct AVL_Node {
    int key;
    AVL_Node* left;
    AVL_Node* right;
    int height;

    // constructor
    AVL_Node(int key) {
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
    }
    AVL_Node(){}
};

#endif //AVL_NODE_H