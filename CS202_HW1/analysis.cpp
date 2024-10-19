//
// Created by Msı on 8.10.2024.
//
/**
* Title: Binary Search Trees
* Author : Halil Arda Özongun
* ID: 22202709
* Section : 1
* Homework : 1
* Description : This is the implementation file for analysis class.
*
*/

#include "analysis.h"
#include "BST.h"

// This function generates 10000 random numbers and inserts them into the BST,
// then it calculates the time taken for each 1000 insertions and the height of the tree.
void analysis::timeAnalysis() {

    srand(time(0));

    int numbers[10000];
    bool exists[10000] = {false};
    for (int i = 0; i < 10000; i++) {
        int num = rand() % 10000;
        while (exists[num]) {
            num = rand() % 10000;
        }
        numbers[i] = num;
        exists[num] = true;
    }

    BST bst;

    for (int i = 0; i < 10; ++i) {
        clock_t start = clock();

        // Insert 1000 numbers
        for (int j = 0; j < 1000; ++j) {
            bst.insertKey(numbers[i * 1000 + j]);
        }

        clock_t end = clock();
        double elapsed_time = double(end - start) / CLOCKS_PER_SEC;

        // Calculate tree height
        int height = bst.calculateTreeHeight(bst.root);

        // Display results
        cout << "After " << (i + 1) * 1000 << " insertions:" << endl;
        cout << "Time taken: " << elapsed_time << " seconds" << endl;
        cout << "Tree height: " << height << endl;
        cout << endl;
    }



}
