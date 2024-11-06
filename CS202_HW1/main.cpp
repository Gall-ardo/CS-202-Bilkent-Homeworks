#include "BST.h"
#include "analysis.h"


int main() {

    int keys[] = {10,7,20,5,9,15,21,2,12,18,24,3,19};
    int size = 13;
    BST bst(keys, size);
    bst.findFullBTLevel();
    bst.lowestCommonAncestor(3,9);
    bst.lowestCommonAncestor(12,15);
    bst.maximumSumPath();
    bst.maximumWidth();
    bst.pathFromAtoB(2,21);
    bst.insertKey(8);
    bst.insertKey(7);
    bst.deleteKey(10);
    bst.deleteKey(11);
    bst.displayInorder();

    return 0;
}


/*
BST with size 13 is created.
Full binary tree level is: 3
Lowest common ancestor of 3 and 9 is: 7
Lowest common ancestor of 12 and 15 is: 15
Maximum sum path is: 10, 20, 15, 18, 19
Maximum level is: 5, 9, 15, 21
Path from 2 to 21 is: 2, 5, 7, 10, 20, 21
Key 8 is added.
Key 7 is not added. It exists!
Key 10 is deleted.
Key 11 is not deleted. It does not exist!
Inorder display is: 2, 3, 5, 7, 8, 9, 12, 15, 18, 19, 20, 21, 24
*/