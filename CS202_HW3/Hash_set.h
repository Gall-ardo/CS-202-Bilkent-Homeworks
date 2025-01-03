#ifndef HASH_SET_H
#define HASH_SET_H

#include "linkedList.h"

template <typename T>
class Hash_set {
    LinkedList<T> *table;
    int size; // size of the table, number of buckets
    int elementCount;

    // hash function
    int hash(T key) const {
        return key % size; // TODO: implement a better hash function
    }

public:
    Hash_set() {
        size = 0;
        table = nullptr;
        elementCount = 0;
    }

    Hash_set(int size) {
        this->size = size;
        table = new LinkedList<T>[size];
        elementCount = 0;
    }

    // destructor
    ~Hash_set() {
        if(table != nullptr) {
            delete[] table;
        }
    }

    // Copy constructor
    Hash_set(const Hash_set& other) {
        size = other.size;
        table = new LinkedList<T>[size];
        elementCount = other.elementCount;
        for (int i = 0; i < size; i++) {
            table[i] = other.table[i];
        }
    }

    // TODO: Assignment operator later if needed

    // insert a key. Assuming table isn't empty
    bool insert(T key) {
        int index = hash(key);
        if (table[index].contains(key)) {
            return false;
        }
        table[index].push_back(key);
        elementCount++;
        return true;
    }
    // remove a key. Assuming table isn't empty
    bool remove(T key) {
        int index = hash(key);
        if (table[index].remove(key)) {
            elementCount--;
            return true;
        }
        return false;
    }
    // check if a key is in the set
    bool contains(T key) const {
        int index = hash(key);
        return table[index].contains(key);
    }


    int getSize() const {
        return size;
    }
    int getElementCount() {
        return elementCount;
    }
    bool isEmpty() {
        return elementCount == 0;
    }

    void clear() {
        for (int i = 0; i < size; i++) {
            table[i].clear();
        }
        elementCount = 0;
    }




};



#endif //HASH_SET_H
