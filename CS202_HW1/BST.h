/**
* Title: Binary Search Trees
* Author : Halil Arda Özongun
* ID: 22202709
* Section : 1
* Homework : 1
* Description : This is the class for BST, which includes the functions which wanted
* in the homework pdf: constructor, destructor, insertKey, deleteKey, displayInorder,
* findFullBTLevel, lowestCommonAncestor, maximumSumPath, maximumWidth, pathFromAtoB.
* For analysis part, calculateTreeHeight function is also added.
* It has helper functions which I defined to help other functions:
* checkIfKeyExists, insertKeyHelper, displayInorderHelper, deleteKeyHelper,
* checkIfKeyExistsHelper, processLeftMost, deleteTree, lowestCommonAncestorHelper.
*/

#ifndef BST_H
#define BST_H

#include <iostream>
using namespace std;
#include "Node.h"
#include "linkedList.h"
#include "queue.h"


class BST {
private:
    bool checkIfKeyExists(int key);
    void insertKeyHelper(Node*& root, int key);
    void displayInorderHelper(Node* root, int& counter);
    bool deleteKeyHelper(Node*& root, int key);
    bool checkIfKeyExistsHelper(Node* root, int key);
    void processLeftMost(Node*& root, Node*& temp);
    void deleteTree(Node* root);
    Node* lowestCommonAncestorHelper( int A, int B);
    void pathfromLCAtoN(int N,Node* LCA, LinkedList<int>* path);


public:
    Node *root;
    int size;
    int height;

    BST(int keys[], int size);
    BST();
    ~BST();
    void insertKey(int key);
    void deleteKey(int key);
    void displayInorder();
    void findFullBTLevel();
    void lowestCommonAncestor(int A, int B);
    void maximumSumPath();
    void maximumWidth();
    void pathFromAtoB(int A, int B);
    int calculateTreeHeight(Node* root);

};


#endif //BST_H
