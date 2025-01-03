/**
* Title: Hashing
* Author : Halil Arda Özongun
* ID: 22202709
* Section : 1
* Homework : 3
* Description : Finding lexicographically smallest insertion order
*/

#include <iostream>
#include <fstream>
#include "linkedList.h"
using namespace std;

void lexicographic(int n, int* hashTable) {
    // Count non-empty slots
    int validEntries = 0;
    for (int i = 0; i < n; i++) {
        if (hashTable[i] != -1) {
            validEntries++;
        }

    }

    LinkedList<int>* dependencies = new LinkedList<int>[n];
    int* dependencyCount = new int[n]();
    bool* processed = new bool[n]();
    int* result = new int[validEntries];
    int resultSize = 0;

    for (int curr = 0; curr < n; curr++) {
        if (hashTable[curr] == -1) {
            continue;
        }

        int startPos = hashTable[curr] % n;
        int pos = startPos;

        while (pos != curr) {
            if (hashTable[pos] != -1) {
                dependencies[pos].push_back(curr);
                dependencyCount[curr]++;
            }else {
                cout << "Impossible" << endl;
                delete[] result;
                delete[] processed;
                delete[] dependencies;
                delete[] dependencyCount;
                return;
            }
            pos = (pos + 1) % n;
        }
    }

    for (int count = 0; count < validEntries; count++) {
        int nextElement = -1;
        for (int i = 0; i < n; i++) {
            if (hashTable[i] != -1 && !processed[i] && dependencyCount[i] == 0) {
                if (nextElement == -1 || hashTable[i] < hashTable[nextElement]) {
                    nextElement = i;
                }
            }
        }

        result[resultSize++] = hashTable[nextElement];
        processed[nextElement] = true;

        LinkedListNode<int>* dep = dependencies[nextElement].head;
        while (dep != nullptr) {
            dependencyCount[dep->data]--;
            dep = dep->next;
        }
    }

    for (int i = 0; i < validEntries; i++) {
        cout << result[i];
        if (i < validEntries - 1) cout << " ";
    }
    cout << endl;


    delete[] result;
    delete[] processed;
    delete[] dependencies;
    delete[] dependencyCount;
}

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    if (argc > 2) {
        freopen(argv[2], "w", stdout);
    }

    // Process input file
    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        cerr << "Could not open input file" << endl;
        return 1;
    }

    int tableSize;
    inputFile >> tableSize;

    int* hashTable = new int[tableSize];
    for (int i = 0; i < tableSize; i++) {
        inputFile >> hashTable[i];
    }

    lexicographic(tableSize, hashTable);

    delete[] hashTable;
    inputFile.close();
    return 0;
}