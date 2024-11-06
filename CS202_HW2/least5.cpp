/**
* Title: Heap and AVL Trees
* Author : Halil Arda Özongun
* ID: 22202709
* Section : 1
* Homework : 2
* Description : question 1
*/

#include <iostream>
#include <fstream>
#include "Heap.h"
using namespace std;

bool minHeapCompare(int a, int b) {
    return a < b;
}

int main(int argc, char* argv[]) {

    ifstream inputFile(argv[1]);
    ofstream outputFile(argv[2]);

    int n = 0;
    inputFile >> n;

    Heap<int> hp(minHeapCompare);

    while (n--) {
        char ch;
        inputFile >> ch;

        switch(ch) {
            case 'a': {
                int val = 0;
                inputFile >> val;
                hp.insert(val);
                break;
            }
            case 'r': {
                if(hp.isEmpty()) {
                    outputFile << -1 << endl;
                } else {
                    hp.extractTop();
                }
                break;
            }
            case 'g': {
                int* arr = new int[5];
                int s = 0;
                hp.getLeast5(arr, s);
                if(s != 5) {
                    outputFile << -1 << endl;
                } else {
                    for(int i = 0; i < 5; i++) {
                        outputFile << arr[i] << endl;
                    }
                }
                delete[] arr;
                break;
            }
        }
    }

    // Close the files
    inputFile.close();
    outputFile.close();

    return 0;
}
