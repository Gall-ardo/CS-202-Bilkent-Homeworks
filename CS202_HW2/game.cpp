/**
* Title: Heap and AVL Trees
* Author : Halil Arda Özongun
* ID: 22202709
* Section : 1
* Homework : 2
* Description : question 2
*/

#include <iostream>
#include <fstream>
#include "AVL_Tree.h"
using namespace std;

int main(int argc, char* argv[]) {

    ifstream inputFile(argv[1]);
    ofstream outputFile(argv[2]);

    int n = 0;
    inputFile >> n;

    int* player1 = new int[n];
    int* player2 = new int[n];
    for(int i = 0; i < n; i++) {
        inputFile >> player1[i];
    }
    for(int i = 0; i < n; i++) {
        inputFile >> player2[i];
    }

    AVL_Tree player1Tree(player1, n);
    AVL_Tree player2Tree(player2, n);

    int counter = 0;
    int player1Score = 0;
    int player2Score = 0;
    bool player1Turn = true;

    while (counter < n) {
        if(player1Turn) {
            int player1Max = player1Tree.findMax(); // O(logN)
            // find the biggest number in player2 which is smaller than player1Max. so
            int player2Max = player2Tree.findPredecessor(player1Max);

            // if player2max is -1 means all numbers are bigger than player1max
            if(player2Max == -1) {
                player2Score++;
                // remove biggest number from player2
                player2Tree.remove(player2Tree.findMax());
            } else { // if a number is found, player1 wins, means it is predecessor of player1max
                player1Score++;
                player2Tree.remove(player2Max);
            }
            player1Tree.remove(player1Max);
            player1Turn = false;
        } else {
            int player2Max = player2Tree.findMax();
            int player1Max = player1Tree.findPredecessor(player2Max);

            if(player1Max == -1) {
                player1Score++;
                player1Tree.remove(player1Tree.findMax());
            } else {
                player2Score++;
                player1Tree.remove(player1Max);
            }
            player2Tree.remove(player2Max);
            player1Turn = true;
        }
        counter++;
    }

    // save scores
    outputFile << player1Score << " " << player2Score << endl;

    // prevent memory leak
    delete[] player1;
    delete[] player2;

    // Close the files
    inputFile.close();
    outputFile.close();

    return 0;
}
