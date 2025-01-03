/**
* Title: Hashing
* Author : Halil Arda Özongun
* ID: 22202709
* Section : 1
* Homework : 3
* Description : Substring matching using hashing with improved rolling hash logic
*/

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
#define ll long long
#define mod1 1000000009
#define mod2 1000000007

struct dataS {
    ll hash1;
    ll hash2;
    int index;
    int count;
    dataS(ll hash1, ll hash2, int index, int count){
        this->hash1 = hash1;
        this->hash2 = hash2;
        this->index = index;
        this->count = count;
    }
    dataS(){
        this->hash1 = -1;
        this->hash2 = -1;
        this->index = -1;
        this->count = 0;
    }
};

bool compare(dataS a, dataS b){
    if(a.hash1 == b.hash1){
        return a.hash2 < b.hash2;
    }
    return a.hash1 < b.hash1;
}

bool compareFix(dataS a, dataS b){
    return a.index < b.index;
}

dataS* tuples;

ll fastPow(ll base, ll exp, ll modulo) {
    if (exp == 0) return 1;
    if (exp % 2 == 1) return (base * fastPow(base, exp - 1, modulo)) % modulo;
    ll half = fastPow(base, exp/2, modulo);
    return (half * half) % modulo;
}

int binarySearch(int left, int right, ll hash1, ll hash2){
    while(left <= right){
        int mid = (left + right) / 2;
        if(tuples[mid].hash1 == hash1 && tuples[mid].hash2 == hash2){
            return mid;
        }
        else if(tuples[mid].hash1 < hash1 || (tuples[mid].hash1 == hash1 && tuples[mid].hash2 < hash2)){
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    return -1;
}

void substrings(string s, int m, string patterns[]) {
    tuples = new dataS[m];
    int lengthOfSmallestPattern = patterns[0].length();
    int biggestPattern = patterns[0].length();

    for(int i = 0; i < m; i++){
        ll hash1 = 0;
        ll hash2 = 0;
        ll p = 31;

        // Calculate hash from right to left
        for(int j = patterns[i].length() - 1; j >= 0; j--) {
            hash1 = (hash1 * p + (patterns[i][j] - 'a' + 1)) % mod1;
            hash2 = (hash2 * p + (patterns[i][j] - 'a' + 1)) % mod2;
        }

        tuples[i] = dataS(hash1, hash2, i, 0);
        lengthOfSmallestPattern = min(lengthOfSmallestPattern, (int)patterns[i].length());
        biggestPattern = max(biggestPattern, (int)patterns[i].length());
    }

    sort(tuples, tuples + m, compare);

    biggestPattern = max(biggestPattern, lengthOfSmallestPattern + 5);

    for(int len = lengthOfSmallestPattern; len <= biggestPattern; len++){
        ll hash1 = 0;
        ll hash2 = 0;
        ll p = 31;

        for(int j = len - 1; j >= 0; j--) {
            hash1 = (hash1 * p + (s[j] - 'a' + 1)) % mod1;
            hash2 = (hash2 * p + (s[j] - 'a' + 1)) % mod2;
        }

        int index = binarySearch(0, m - 1, hash1, hash2);
        if(index != -1 && patterns[tuples[index].index].length() == len) {
            tuples[index].count++;
        }

        ll power1 = fastPow(p, mod1 - 2, mod1);
        ll power2 = fastPow(p, mod2 - 2, mod2);
        ll highestPow1 = fastPow(p, len - 1, mod1);
        ll highestPow2 = fastPow(p, len - 1, mod2);

        for(int j = len; j < s.length(); j++) {
            hash1 = ((hash1 - (s[j - len] - 'a' + 1) + mod1) * power1) % mod1;
            hash2 = ((hash2 - (s[j - len] - 'a' + 1) + mod2) * power2) % mod2;

            hash1 = (hash1 + ((s[j] - 'a' + 1) * highestPow1)) % mod1;
            hash2 = (hash2 + ((s[j] - 'a' + 1) * highestPow2)) % mod2;

            index = binarySearch(0, m - 1, hash1, hash2);
            if(index != -1 && patterns[tuples[index].index].length() == len) {
                tuples[index].count++;
            }
        }
    }

    sort(tuples, tuples + m, compareFix);

    for(int i = 0; i < m; i++){
        cout << tuples[i].count << endl;
    }

    delete[] tuples;
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

    string text;
    input >> text;

    int m;
    input >> m;

    string* patterns = new string[m];
    for (int i = 0; i < m; i++) {
        input >> patterns[i];
    }

    substrings(text, m, patterns);

    delete[] patterns;
    input.close();

    return 0;
}