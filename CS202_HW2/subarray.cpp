/**
* Title: Heap and AVL Trees
* Author : Halil Arda Özongun
* ID: 22202709
* Section : 1
* Homework : 2
* Description : question 4
*/

#include <iostream>
#include <fstream>
#include "AVL_Tree.h"

using namespace std;


int main(int argc, char* argv[]) {
    ifstream inputFile(argv[1]);
    ofstream outputFile(argv[2]);

    int n = 0, m = 0, k = 0;
    inputFile >> n >> m >> k;

    int* bigArray = new int[n];
    int* smallArray = new int[n];

    for(int i = 0; i < n; i++) {
        inputFile >> bigArray[i];
    }

    for(int i = 0; i < n; i++) {
        inputFile >> smallArray[i];
    }

    int begginning = max(m,k) - 1;

    int leftPointer = 0;
    int rightPointer = begginning;

    int workingMinSize = 1e9 + 7;

    AVL_Tree bigArrayTree;
    AVL_Tree smallArrayTree;
    AVL_Tree bigNonUsed;
    AVL_Tree smallNonUsed;

    for(int i = 0; i < m; i++) {
        bigArrayTree.insert(bigArray[i]);
    }

    for(int i = m; i <= begginning; i++) {
        if(bigArray[i] > bigArrayTree.findMin()) {
            int minVal = bigArrayTree.findMin();
            bigNonUsed.insert(minVal);
            bigArrayTree.remove(minVal);
            bigArrayTree.insert(bigArray[i]);
        }else {
            // insert to bigNonUsed
            bigNonUsed.insert(bigArray[i]);

        }
    }

    for(int i = 0; i < k; i++) {
        smallArrayTree.insert(smallArray[i]);
    }

    for(int i = k; i <= begginning; i++) {
        if(smallArray[i] < smallArrayTree.findMax()) {
            int maxVal = smallArrayTree.findMax();
            smallNonUsed.insert(maxVal);
            smallArrayTree.remove(maxVal);
            smallArrayTree.insert(smallArray[i]);

        }else {
            // insert to smallNonUsed
            smallNonUsed.insert(smallArray[i]);
        }
    }

    while (true) {
        int bigArrMin = bigArrayTree.findMin();
        int smallArrMax = smallArrayTree.findMax();


        if(bigArrMin > smallArrMax) {
            workingMinSize = min(workingMinSize, rightPointer - leftPointer + 1);
            if(bigArrayTree.remove(bigArray[leftPointer])) {
                bigArrayTree.insert(bigNonUsed.findMax());
                bigNonUsed.remove(bigNonUsed.findMax());
            }
            else {
                bigNonUsed.remove(bigArray[leftPointer]);
            }

            if(smallArrayTree.remove(smallArray[leftPointer])) {
                smallArrayTree.insert(smallNonUsed.findMin());
                smallNonUsed.remove(smallNonUsed.findMin());
            }
            else {
                smallNonUsed.remove(smallArray[leftPointer]);
            }
            leftPointer++;
        }
        else {
            rightPointer++;
            if(rightPointer >= n) {
                break;
            }

            if(bigArray[rightPointer] > bigArrayTree.findMin()) {
                bigNonUsed.insert(bigArrayTree.findMin());
                bigArrayTree.remove(bigArrayTree.findMin());
                bigArrayTree.insert(bigArray[rightPointer]);
            }
            else {
                bigNonUsed.insert(bigArray[rightPointer]);
            }

            if(smallArray[rightPointer] < smallArrayTree.findMax()) {
                smallNonUsed.insert(smallArrayTree.findMax());
                smallArrayTree.remove(smallArrayTree.findMax());
                smallArrayTree.insert(smallArray[rightPointer]);
            }
            else {
                smallNonUsed.insert(smallArray[rightPointer]);
            }
        }
    }

    if(workingMinSize == 1e9 + 7) {
        workingMinSize = -1;
    }
    outputFile << workingMinSize << endl;

    delete[] bigArray;
    delete[] smallArray;
    inputFile.close();
    outputFile.close();

    return 0;
}