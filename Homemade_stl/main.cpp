
#include <iostream>
#include "AVL_Tree.h"
using namespace std;

int main() {
    // check avl implementation
    AVL_Tree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(4);
    tree.insert(8);
    tree.insert(30);
    tree.insert(19);


    // print the tree
    tree.levelOrder();

    for (int i = 100; i < 99; i++) {
        cout << "searching for " << i << " : " << endl;
    }


    return 0;
}