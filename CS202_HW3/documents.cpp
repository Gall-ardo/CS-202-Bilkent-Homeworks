/**
* Title: Hashing
* Author : Halil Arda Özongun
* ID: 22202709
* Section : 1
* Homework : 3
* Description : Document compression using hashing
*/

#include <iostream>
#include <fstream>
#include "HashTable.h"
using namespace std;

void documents(int n, string docs[]) {
    // TODO: Implement the logic to:
    // 1. Find minimum number of documents needed
    // 2. Consider all possible operations:
    //    - Add one character
    //    - Delete one character
    //    - Change one character
    //    - Cyclic shifting
    // 3. Group similar documents that can be converted to each other

    // Output format:
    // cout << minimum_number_of_documents << endl;
}

int main1(int argc, char* argv[]) {
    // Handle output redirection if output file provided
    if (argc > 2) {
        freopen(argv[2], "w", stdout);
    }

    // Open the input file
    ifstream input(argv[1]);
    if (!input.is_open()) {
        cerr << "Could not open input file" << endl;
        return 1;
    }

    // Read number of documents
    int n;
    input >> n;
    input.ignore(); // Skip newline after n

    // Read the documents
    string* docs = new string[n];
    for (int i = 0; i < n; i++) {
        getline(input, docs[i]);
    }

    // Call the function
    documents(n, docs);

    // Cleanup
    delete[] docs;
    input.close();

    return 0;
}