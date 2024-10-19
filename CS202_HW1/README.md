# Binary Search Tree Implementation

## Overview

This project implements a pointer-based Binary Search Tree (BST) where each node contains an integer key. The BST is encapsulated in a class called `BST`, with its interface defined in `BST.h` and implementation in `BST.cpp`. The class supports various operations, including inserting and deleting nodes, finding paths, and performing tree traversal.

## Class Description

### `BST`

The main class for the BST implementation. It includes public member functions for tree operations and private helper functions.

### Public Member Functions

1. **`BST(int keys[], int size)`**: Constructor that creates a BST from an array of integer keys by inserting them one by one.

2. **`BST()`**: Default constructor that initializes an empty tree.

3. **`~BST()`**: Destructor that deletes all nodes and frees memory.

4. **`void insertKey(int key)`**: Inserts a key into the tree if it does not already exist.

5. **`void deleteKey(int key)`**: Deletes a key from the tree if it exists.

6. **`void displayInorder()`**: Displays an inorder traversal of the tree.

7. **`void findFullBTLevel()`**: Finds the maximum level at which the tree forms a full binary tree and displays the level number.

8. **`void lowestCommonAncestor(int A, int B)`**: Finds and displays the lowest common ancestor of two keys, A and B.

9. **`void maximumSumPath()`**: Finds the path from the root to a leaf node that has the maximum sum of keys and displays the keys in the path.

10. **`void maximumWidth()`**: Finds the level with the maximum number of nodes and displays the keys at that level.

11. **`void pathFromAtoB(int A, int B)`**: Finds and displays the path from key A to key B.

### Private Member Functions

1. **`void deleteTree(Node* root)`**: Helper function for the destructor that recursively deletes all nodes.

2. **`void insertKeyHelper(Node*& root, int key)`**: Recursive helper for `insertKey` that adds a key to the tree.

3. **`bool deleteKeyHelper(Node*& root, int key)`**: Recursive helper for `deleteKey` that removes a node.

4. **`void processLeftMost(Node*& root, Node*& temp)`**: Finds the leftmost node (successor) for deletion.

5. **`void displayInorderHelper(Node* root, int& counter)`**: Recursive helper for `displayInorder`.

6. **`Node* lowestCommonAncestorHelper(int A, int B)`**: Helper function to find the lowest common ancestor iteratively.

7. **`void pathfromLCAtoN(int N, Node* LCA, LinkedList<int>* path)`**: Finds the path from a given node (LCA) to a specified key.

8. **`int calculateTreeHeight(Node* root)`**: Calculates the height of the tree.

9. **`bool checkIfKeyExists(int key)`**: Checks if a given key exists in the tree.

10. **`bool checkIfKeyExistsHelper(Node* root, int key)`**: Recursive helper for `checkIfKeyExists`.
