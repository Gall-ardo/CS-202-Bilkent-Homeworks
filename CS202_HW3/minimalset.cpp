#include <iostream>
#include <fstream>
#include <cstdint>
#include <algorithm>
using namespace std;

#define ll long long
#define mod1 1000000009
#define mod2 1000000007

struct HashPair {
    ll hash1;
    ll hash2;
    int index;

    bool operator<(const HashPair& other) const {
        if (hash1 == other.hash1) {
            return hash2 < other.hash2;
        }
        return hash1 < other.hash1;
    }
    bool operator==(const HashPair& other) const {
        return hash1 == other.hash1 && hash2 == other.hash2;
    }
};

string revString(const string& s) {
    string rev = "";
    for (int i = s.length() - 1; i >= 0; i--) {
        rev += s[i];
    }
    return rev;
}

HashPair* hashes;

int checkExist(pair<int, int> hash, int n) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int mid = (r+l) / 2;

        if (hashes[mid].hash1 == hash.first && hashes[mid].hash2 == hash.second) {
            while (mid > 0 && hashes[mid-1].hash1 == hash.first && hashes[mid-1].hash2 == hash.second) {
                mid--;
            }
            return mid;
        }
        if (hashes[mid].hash1 < hash.first || (hashes[mid].hash1 == hash.first && hashes[mid].hash2 < hash.second)) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return -1;
}

pair<int, int> hashV(const string& s) {
    int n = s.length();
    const ll p = 31;

    ll high_pow1 = 1, high_pow2 = 1;
    for (int i = 0; i < n-1; i++) {
        high_pow1 = (high_pow1 * p) % mod1;
        high_pow2 = (high_pow2 * p) % mod2;
    }

    ll hash1 = 0, hash2 = 0;
    for (int i = 0; i < n; i++) {
        hash1 = (hash1 * p + (s[i] - 'a' + 1)) % mod1;
        hash2 = (hash2 * p + (s[i] - 'a' + 1)) % mod2;
    }

    ll min_hash1 = hash1;
    ll min_hash2 = hash2;
    ll curr_hash1 = hash1;
    ll curr_hash2 = hash2;

    for (int i = 0; i < n-1; i++) {
        curr_hash1 = ((curr_hash1 - (s[i] - 'a' + 1) * high_pow1 % mod1 + mod1) * p +
                     (s[i] - 'a' + 1)) % mod1;
        min_hash1 = min(min_hash1, curr_hash1);

        curr_hash2 = ((curr_hash2 - (s[i] - 'a' + 1) * high_pow2 % mod2 + mod2) * p +
                     (s[i] - 'a' + 1)) % mod2;
        min_hash2 = min(min_hash2, curr_hash2);
    }

    return {(int)min_hash1, (int)min_hash2};
}

pair<int, int> minimalset(int n, string* strings) {


    hashes = new HashPair[n];
    for (int i = 0; i < n; i++) {
        pair<int, int> hash = hashV(strings[i]);
        hashes[i] = {hash.first, hash.second, i};
    }

    sort(hashes, hashes + n);

    int numberOfReverses = 0;
    int numberOfSets = 0;

    int* reverseCount = new int[n];
    for (int i = 0; i < n; i++) {
        reverseCount[i] = 0;
    }

    for(int i = 0; i < n; i++) {
        HashPair currHash = hashes[i];
        int start = i;
        int end = i + 1;
        while (end < n && hashes[end] == currHash) {
            end++;
        }

        if(reverseCount[currHash.index] == 0) {
            numberOfSets++;

            string reversed = revString(strings[currHash.index]);
            pair<int, int> revHash = hashV(reversed);
            int reverseIdx = checkExist(revHash, n);

            if(reverseIdx != -1) {
                reverseCount[hashes[reverseIdx].index] = end - start;

            }
        }
        else {
            if(end - start < reverseCount[currHash.index]) {
                numberOfReverses += end - start;
            } else {
                numberOfReverses += reverseCount[currHash.index];
            }
        }
        i = end - 1;
    }


    delete[] reverseCount;
    delete[] hashes;
    return {numberOfReverses, numberOfSets};
}

int main(int argc, char* argv[]) {
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

    string* strings = new string[n];
    for (int i = 0; i < n; i++) {
        input >> strings[i];
    }

    pair<int, int> result = minimalset(n, strings);
    cout << result.first << endl;
    cout << result.second << endl;

    delete[] strings;
    input.close();

    return 0;
}
