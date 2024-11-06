/**
* Title: Heap and AVL Trees
* Author : Halil Arda Özongun
* ID: 22202709
* Section : 1
* Homework : 2
* Description : question 3
*/

#include <iostream>
#include <fstream>
#include "Heap.h"
using namespace std;

bool minHeapCompare(int a, int b) {
    return a < b;
}
bool maxHeapCompare(int a, int b) {
    return a > b;
}

int main(int argc, char* argv[]) {

    ifstream inputFile(argv[1]);
    ofstream outputFile(argv[2]);

    int n = 0, m = 0;
    inputFile >> n >> m;

    int* bigArray = new int[n];
    int* smallArray = new int[n];
    for(int i = 0; i < n; i++) {
        inputFile >> bigArray[i];
    }
    for(int i = 0; i < n; i++) {
        inputFile >> smallArray[i];
    }

    int leftIndex = m - 1;
    int rightIndex = n - 1;
    int smalestPossible = 1e9 + 7;

    while (leftIndex <= rightIndex) {
        int mid = (leftIndex + rightIndex) / 2;

        // save to heaps. A max heap and a min heap
        Heap<int> minHeap(m, minHeapCompare);
        Heap<int> maxHeap(m, maxHeapCompare);


        for(int i = 0; i < m; i++) {
            minHeap.insert(bigArray[i]);
            maxHeap.insert(smallArray[i]);
        }

        // now for rest mid - m elements, if the ith element is bigger than the top element of minHeap. remove the top element of minHeap and insert the ith element
        for(int i = m; i <= mid; i++) {
            if(bigArray[i] > minHeap.top()) {
                minHeap.extractTop(); // remove the smallest
                minHeap.insert(bigArray[i]); // add sth bigger
            }
            if(smallArray[i] < maxHeap.top()) {
                maxHeap.extractTop();
                maxHeap.insert(smallArray[i]);
            }
        }

        int* maxHeapArray = minHeap.getHeap();
        int* minHeapArray = maxHeap.getHeap();

        // compare results
        int counter = 0;
        for(int i = 0; i < m; i++) {
            if(maxHeapArray[i] > minHeapArray[m-i-1]) {
                counter++;
            }
        }

        delete[] maxHeapArray;
        delete[] minHeapArray;

        if(counter == m) {
            smalestPossible = min(smalestPossible, mid);
            rightIndex = mid - 1;
        }
        else {
            leftIndex = mid + 1;
        }
    }

    if(smalestPossible == 1e9 + 7) {
        smalestPossible = -1;
    } else {
        smalestPossible++;
    }

    outputFile << smalestPossible << endl;

    delete[] bigArray;
    delete[] smallArray;

    // Close the files
    inputFile.close();
    outputFile.close();

    return 0;
}
