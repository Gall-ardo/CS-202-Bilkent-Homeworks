/**
* Title: Hashing
* Author : Halil Arda Özongun
* ID: 22202709
* Section : 1
* Homework : 3
* Description : Counting possible insertion orders for hash table
*/

#include <iostream>
#include <fstream>
using namespace std;
#define ll long long
#define MOD 1000000009

void insertionOrders(int n, int* table){
    int divide2 = 0;
    int divide3 = 0;
    int validNum = 0;
    bool prevValueCorrectPlace = true;

    for (int i = 0; i < n; i++) {
        int hashValue = table[i] % n;

        if( table[i] != -1){
            validNum++;
        }

        if (hashValue == i || table[i] == -1) {
            prevValueCorrectPlace = true;
        }
        else if (hashValue == ((i - 1 + n) % n)) {
            if (prevValueCorrectPlace) {
                divide2++;
            } else {
                divide3++;
            }
            prevValueCorrectPlace = false;
        }
        else if (hashValue == ((i - 2 + n) % n)) {
            if (prevValueCorrectPlace) {
                divide3++;
            } else {
                divide3++;
            }
            prevValueCorrectPlace = false;
        }
    }


    ll* dp = new ll[validNum + 1];
    for (int i = 0; i <= validNum; i++) {
        dp[i] = i;
    };

    int lastIndexCalculated = 1;
    for(int i = 0; i < divide2; i++) {
        while (dp[lastIndexCalculated] % 2 != 0) {
            lastIndexCalculated++;
        }
        dp[lastIndexCalculated] /= 2;
    }

    lastIndexCalculated = 1;
    for(int i = 0; i < divide3; i++) {
        while (dp[lastIndexCalculated] % 3 != 0) {
            lastIndexCalculated++;
        }
        dp[lastIndexCalculated] /= 3;
    }


    ll result = 1;
    for (int i = 1; i <= validNum; i++) {
        result = (result * dp[i]) % MOD;
    }
    cout << result << endl;

    delete[] dp;
}

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);


    if (argc > 2) {
        freopen(argv[2], "w", stdout);
    }

    ifstream input(argv[1]);
    if (!input.is_open()) {
        cerr << "Could not open input file" << endl;
        return 1;
    }

    int n;
    input >> n;
    int* table = new int[n];
    for (int i = 0; i < n; i++) {
        input >> table[i];
    }

    insertionOrders(n, table);

    delete[] table;
    input.close();

    return 0;
}