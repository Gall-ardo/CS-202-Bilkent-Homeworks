/**
* Title: Binary Search Trees
* Author : Halil Arda Özongun
* ID: 22202709
* Section : 1
* Homework : 1
* Description : This is a node struct for binary search tree implementation, it has key, left and right pointers.
*/

#ifndef NODE_H
#define NODE_H


struct Node {
    int key;
    Node* left;
    Node* right;

    // constructor
    Node(int key) {
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
    }
    Node(){}
};

#endif //NODE_H
