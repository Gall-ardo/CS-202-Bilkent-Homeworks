/**
* Title: Binary Search Trees
* Author : Halil Arda Özongun
* ID: 22202709
* Section : 1
* Homework : 1
* Description : This is the implementation file for binary search tree.
*/

#include "BST.h"
using namespace std;


// Constructor
BST::BST(int keys[], int size) {
    root = nullptr;
    for (int i = 0; i < size; i++) {
        insertKeyHelper(root, keys[i]);
    }
    this->size = size;
    cout << "BST with size " << size << " is created." << endl;
}

// Default constructor
BST::BST() {
    root = nullptr;
    size = 0;
    cout << "BST with size 0 is created." << endl;
}

// Destructor
BST::~BST() {
    deleteTree(root);
}

// This function is used to delete the tree, as a helper function for the destructor
void BST::deleteTree(Node* root) {
    if (root == nullptr) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
    root = nullptr;
    size--;
}

// Insert key
void BST::insertKey(int key) {
    if(checkIfKeyExists(key)) {
        cout << "Key " << key << " is not added. It exists!" << endl;
        return;
    }
    insertKeyHelper(root, key);
    cout << "Key " << key << " is added." << endl;
    size++;
}

// Helper function for insertKey, recursive. Just adds the node, if you call, you have to increment the size by hand.
void BST::insertKeyHelper(Node*& root, int key) {
    if (root == nullptr) {
        root = new Node(key);
        return;
    }
    if (key < root->key) {
        insertKeyHelper(root->left, key);
    } else {
        insertKeyHelper(root->right, key);
    }
}

// Delete key
void BST::deleteKey(int key) {
    if(size == 0) {
        cout << "Key " << key << " is not deleted. It does not exist!" << endl;
        return;
    }
    deleteKeyHelper(root, key);
}

// Helper function for deleteKey, recursive
bool BST::deleteKeyHelper(Node *&root, int searchKey) {
    if(root == nullptr) {
        cout << "Key " << searchKey << " is not deleted. It does not exist!" << endl;
        return false;
    }
    if(searchKey == root->key) {
        // Key found: 3 cases:

        if(root->left == nullptr && root->right == nullptr) {  // case 1. No child
            delete root;
            root = nullptr;
        } else if(root->left == nullptr) { // case 2. 1 child
            Node* temp = root;
            root = root->right;
            delete temp;
        } else if(root->right == nullptr) {  // case 2. 1 child
            Node* temp = root;
            root = root->left;
            delete temp;
        } else { // case 3. 2 children
            Node *temp;
            processLeftMost(root->right, temp);
            root->key = temp->key;
            delete temp;
        }
        cout << "Key " << searchKey << " is deleted." << endl;
        size--;
        return true;

    } else if(searchKey < root->key) {
        deleteKeyHelper(root->left, searchKey);
    } else {
        deleteKeyHelper(root->right, searchKey);
    }
    return false;

}

// Finds the smallest number which is bigger than the root, and returns it in temp
void BST::processLeftMost(Node*& root, Node*& temp) {
    if(root->left == nullptr) {
        temp = root;
        root = root->right; // Since this is pointer, the node who points to this node will also be updated
    } else {
        processLeftMost(root->left, temp);
    }
}

// Display inorder
void BST::displayInorder() {
    cout << "Inorder display is: ";
    int counter = 0;
    displayInorderHelper(root, counter);
    cout << endl;
}

// Helper function for displayInorder, recursive
void BST::displayInorderHelper(Node* root, int& counter) {
    if (root == nullptr) {
        return;
    }
    displayInorderHelper(root->left, counter);
    cout << root->key;
    counter++;
    if (counter != size) {
        cout << ", ";
    }
    displayInorderHelper(root->right, counter);
}

// Find full binary tree level
void BST::findFullBTLevel() {
    int level = 1;
    int lastLevelFull = 1;
    int neccesaryToFillThisLevel = 1; // 2 ^ (level - 1)
    int currentNumberOfNodes = 0;

    struct QueueItem {
        Node* node;
        int level;
        QueueItem(Node* node, int level) : node(node), level(level){}
        QueueItem() = default;
    };
    Queue<QueueItem> queue;
    queue.push(QueueItem(root,1));

    while (!queue.isEmpty()) {
        QueueItem curr = queue.getFront();
        queue.pop();

        if(curr.level == level) {
            currentNumberOfNodes++;
            // check if it is full
            if(currentNumberOfNodes == neccesaryToFillThisLevel) {
                lastLevelFull = level;
                level++;
                neccesaryToFillThisLevel *= 2;
                currentNumberOfNodes = 0;
            }
        }else if(curr.level > level) {
            // means that we are in a new level
            level = curr.level;
            currentNumberOfNodes = 1;
            neccesaryToFillThisLevel *= 2;
        }
        if(curr.node->left != nullptr) {
            queue.push(QueueItem(curr.node->left, curr.level + 1));
        }
        if(curr.node->right != nullptr) {
            queue.push(QueueItem(curr.node->right, curr.level + 1));
        }

    }
    cout << "Full binary tree level is: " << lastLevelFull << endl;

}

// Find the lowest common ancestor of A and B
void BST::lowestCommonAncestor(int A, int B) {
    if(!checkIfKeyExists(A) || !checkIfKeyExists(B)) {
        cout << "Error: One or both keys (" << A << ", " << B << ") do not exist in the tree." << endl;
        return;
    }

    Node* result = lowestCommonAncestorHelper(A, B);
    cout << "Lowest common ancestor of " << A << " and " << B << " is: " << result->key << endl;
}

// Helper function for lowestCommonAncestor, iterative
Node* BST::lowestCommonAncestorHelper(int A, int B) {
    Node* result = root;
    while (result != nullptr) {
        // if result is equal to A or B, then it is the lowest common ancestor
        if (result->key == A || result->key == B) {
            break;
        }
        if (A < result->key && B < result->key) {
            result = result->left;
        } else if (A > result->key && B > result->key) {
            result = result->right;
        } else {
            // means A and B are in the different subtrees of the result so result can not get lower
            break;
        }
    }
    return result;
}

// Find the path starting from the root ending in the leaf, with the maximum sum
void BST::maximumSumPath() {
    cout << "Maximum sum path is: ";
    if(root == nullptr) {
        cout << endl;
        return;
    }

    struct QueueItem {
        Node* node;
        int currentSum;
        LinkedList<int>  path;
        QueueItem(Node* node, int currentSum, LinkedList<int> path) : node(node), currentSum(currentSum), path(path){}
        QueueItem() = default;
    };

    Queue<QueueItem> queue;
    LinkedList<int> path;
    path.push_back(root->key);
    queue.push(QueueItem(root, root->key, path));

    int maxSum = -1;
    LinkedList<int> maxPath;

    while (!queue.isEmpty()) {
        QueueItem curr = queue.getFront();
        queue.pop(); // no need to delete the node or linkedlist, because we are not using new keyword

        if(curr.node->left == nullptr && curr.node->right == nullptr) { // leaf node
            if(curr.currentSum > maxSum) {
                maxSum = curr.currentSum;
                maxPath = curr.path;
            }
        } else {
            if(curr.node->left != nullptr) {
                LinkedList<int> newPath = curr.path; // create a new linked list thanks to copy constructor
                newPath.push_back(curr.node->left->key);
                queue.push(QueueItem(curr.node->left, curr.currentSum + curr.node->left->key, newPath));
            }
            if(curr.node->right != nullptr) {
                LinkedList<int> newPath = curr.path;
                newPath.push_back(curr.node->right->key);
                queue.push(QueueItem(curr.node->right, curr.currentSum + curr.node->right->key, newPath));
            }
        }
    }

    // print the maxPath
    LinkedListNode<int>* temp = maxPath.head;
    while (temp != nullptr) {
        cout << temp->data;
        if(temp->next != nullptr) {
            cout << ", ";
        }
        temp = temp->next;
    }
    cout << endl;
}

// Prints the level with the maximum number of nodes
void BST::maximumWidth() {
    int currentLevel = 1;
    int currentLevelNum = 0;
    int maxLevelCount = -1;
    LinkedList<int> maxList;
    LinkedList<int> currentList;

    cout << "Maximum level is: ";

    if(root == nullptr) {
        cout << endl;
        return;
    }

    struct QueueItem {
        Node* node;
        int level;
        QueueItem(Node* node, int level) : node(node), level(level){}
        QueueItem() = default;
    };

    Queue<QueueItem> queue;
    queue.push(QueueItem(root,1));

    while (!queue.isEmpty()) {
        QueueItem curr = queue.getFront();
        queue.pop();
        currentList.push_back(curr.node->key);

        if(currentLevel == curr.level ) {
            currentLevelNum++;

            if(currentLevelNum > maxLevelCount) {
                maxLevelCount = currentLevelNum;
                maxList.clear();
                maxList = currentList;
            }
        }else if(curr.level == currentLevel + 1 ) {
            currentLevel++;
            currentLevelNum = 1;
            currentList.clear();
            currentList.push_back(curr.node->key);

        }
        if(curr.node->left != nullptr) {
            queue.push(QueueItem(curr.node->left, curr.level + 1));
        }

        if(curr.node->right != nullptr) {
            queue.push(QueueItem(curr.node->right, curr.level + 1));
        }
    }

    // print the maxList
    LinkedListNode<int>* temp = maxList.head;
    while (temp != nullptr) {
        cout << temp->data;
        if(temp->next != nullptr) {
            cout << ", ";
        }
        temp = temp->next;
    }
    cout << endl;

}

// Finds the path from A to B
// there are 2 cases:
// A and B is in the different subtrees of the lowest common ancestor
// One of the A or B is the lowest common ancestor
void BST::pathFromAtoB(int A, int B) {
    Node* lowestCommonAncestorNode = lowestCommonAncestorHelper(A, B);

    // Case 1: One of the A or B is the lowest common ancestor
    if(lowestCommonAncestorNode->key == A) {
        LinkedList<int> pathFromLCAtoB;
        pathfromLCAtoN(B, lowestCommonAncestorNode, &pathFromLCAtoB);
        cout << "Path from " << A << " to " << B << " is: ";
        LinkedListNode<int>* temp = pathFromLCAtoB.head;
        while (temp != nullptr) {
            cout << temp->data;
            if(temp->next != nullptr) {
                cout << ", ";
            }
            temp = temp->next;
        }
        cout << endl;
        return;
    }

    if(lowestCommonAncestorNode->key == B) {
        LinkedList<int> pathFromLCAtoA;
        pathfromLCAtoN(A, lowestCommonAncestorNode, &pathFromLCAtoA);
        cout << "Path from " << A << " to " << B << " is: ";
        // since we are going from A to B, we need to print the path in reverse order
        pathFromLCAtoA = pathFromLCAtoA.reverse();
        LinkedListNode<int>* temp = pathFromLCAtoA.head;
        while (temp != nullptr) {
            cout << temp->data;
            if(temp->next != nullptr) {
                cout << ", ";
            }
            temp = temp->next;
        }
        cout << endl;
        return;
    }

    // means they are in the different subtrees of the lowest common ancestor.
    // So, find the way from A to LCA and B to LCA. then print it as A to LCA + LCA to B
    LinkedList<int> pathA = LinkedList<int>();
    LinkedList<int> pathB = LinkedList<int>();

    pathfromLCAtoN(A, lowestCommonAncestorNode, &pathA);
    pathfromLCAtoN(B, lowestCommonAncestorNode, &pathB);

    cout << "Path from " << A << " to " << B << " is: ";
    // print the pathA in reverse order
    pathA = pathA.reverse();
    LinkedListNode<int>* temp = pathA.head;
    while (temp != nullptr) {
        cout << temp->data;
        if(temp->next != nullptr) {
            cout << ", ";
        }
        temp = temp->next;
    }

    cout << ", ";
    // print the pathB
    temp = pathB.head->next; // skip the first element,
    // because it is the LCA, and we already printed it when we printed the pathA
    while (temp != nullptr) {
        cout << temp->data;
        if(temp->next != nullptr) {
            cout << ", ";
        }
        temp = temp->next;
    }
    cout << endl;

}

// Find the path from LCA to N, and return in linked list, iterative
void BST::pathfromLCAtoN(int N, Node *LCA, LinkedList<int> *path) {
    Node* temp = LCA;
    while (temp != nullptr) {
        path->push_back(temp->key);
        if(temp->key == N) {
            break;
        }
        if(N < temp->key) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
}


// This function is used to calculate the height of the tree
int BST::calculateTreeHeight(Node *root) {
    if(root == nullptr) {
        return 0;
    }
    return 1 + max(calculateTreeHeight(root->left), calculateTreeHeight(root->right));
}

// This function is used to check if the key exists in the tree
bool BST::checkIfKeyExists(int key) {
    return checkIfKeyExistsHelper(root, key);
}

// Helper function for checkIfKeyExists, recursive
bool BST::checkIfKeyExistsHelper(Node* root, int key) {
    if (root == nullptr) {
        return false;
    }
    if (root->key == key) {
        return true;
    }
    if (key < root->key) {
        return checkIfKeyExistsHelper(root->left, key);
    }
    return checkIfKeyExistsHelper(root->right, key);
}

