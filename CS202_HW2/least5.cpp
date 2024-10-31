/**
* Title: Heap and AVL Trees
* Author : Halil Arda Özongun
* ID: 22202709
* Section : 1
* Homework : 2
* Description :
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include "Heap.h"

using namespace std;

int main(int argc, char* argv[]) {

    ifstream inputFile(argv[1]);
    ofstream outputFile(argv[2]);

    // Check if files are successfully opened
    if (!inputFile.is_open()) {
        cerr << "Error opening input file." << endl;
        return 1;
    }
    if (!outputFile.is_open()) {
        cerr << "Error opening output file." << endl;
        return 1;
    }

    int n;
    inputFile >> n;

    Heap<int> hp;

    while (--n) {
        char ch;
        inputFile >> ch;
        if (ch == 'a') {
            int val;
            inputFile >> val;
            hp.insert(val);
        } else if (ch == 'r') {
            hp.extractTop();
        } else if (ch == 'q') {
            int* arr = new int[5];
            int s = 0;
            hp.getLeast5(arr, s);
            if (s == -1) {
                outputFile << -1 << endl;
            } else {
                for (int i = 0; i < s; i++) {
                    outputFile << arr[i] << endl;
                }
            }
            delete[] arr;
        }
    }

    // Close the files
    inputFile.close();
    outputFile.close();

    return 0;
}
