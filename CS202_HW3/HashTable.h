#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "linkedList.h"

template<typename K, typename V>
class HashNode {
public:
    K key;
    V value;
    HashNode(const K& k, const V& v) : key(k), value(v) {}
};

template<typename K, typename V>
class HashTable {
    LinkedList<HashNode<K,V>> *table;
    int size; // size of the table, number of buckets
    int elementCount;

    int hash1(K key) const {
        unsigned long hash = 0;
        for (char c : key) {
            hash = (hash * 31 + (c - 'a' + 1)) % size;
        }
        return hash;
    }

    // for numeric keys
    /*int hash2(K key) const {
         return key % size;
    }*/

    // hash function
    int hash(K key) const {
        return hash1(key);
    }

public:
    HashTable() {
        size = 0;
        table = nullptr;
        elementCount = 0;
    }

    HashTable(int size) {
        this->size = size;
        table = new LinkedList<HashNode<K,V>>[size];
        elementCount = 0;
    }

    // destructor
    ~HashTable() {
        if(table != nullptr) {
            delete[] table;
        }
    }

    // Copy constructor
    HashTable(const HashTable& other) {
        size = other.size;
        table = new LinkedList<HashNode<K,V>>[size];
        elementCount = other.elementCount;
        for (int i = 0; i < size; i++) {
            table[i] = other.table[i];
        }
    }

    // TODO: Assignment operator later if needed

    // insert a key-value pair. Assuming table isn't empty
    // if key exists, update value and return false
    bool insert(K key, V value) {
        int index = hash(key);

        // Check if key exists and update value if it does
        LinkedListNode<HashNode<K,V>>* current = table[index].head;
        while (current != nullptr) {
            if (current->data.key == key) {
                current->data.value = value;
                return false;
            }
            current = current->next;
        }

        // Key doesn't exist, insert new node
        table[index].push_back(HashNode<K,V>(key, value));
        elementCount++;
        return true;
    }

    // remove a key-value pair. Assuming table isn't empty
    bool remove(K key) {
        int index = hash(key);

        LinkedListNode<HashNode<K,V>>* current = table[index].head;
        LinkedListNode<HashNode<K,V>>* prev = nullptr;

        while (current != nullptr) {
            if (current->data.key == key) {
                if (prev == nullptr) {
                    table[index].pop_front();
                } else {
                    prev->next = current->next;
                    if (current == table[index].tail) {
                        table[index].tail = prev;
                    }
                    delete current;
                }
                elementCount--;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    // get value associated with key. Return default V if not found
    V get(K key) const {
        int index = hash(key);

        LinkedListNode<HashNode<K,V>>* current = table[index].head;
        while (current != nullptr) {
            if (current->data.key == key) {
                return current->data.value;
            }
            current = current->next;
        }
        return V();  // return default value if key not found
    }

    // check if a key exists in the map
    bool contains(K key) const {
        int index = hash(key);

        LinkedListNode<HashNode<K,V>>* current = table[index].head;
        while (current != nullptr) {
            if (current->data.key == key) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    int getSize() const {
        return size;
    }

    int getElementCount() const {
        return elementCount;
    }

    bool isEmpty() const {
        return elementCount == 0;
    }

    void clear() {
        for (int i = 0; i < size; i++) {
            table[i].clear();
        }
        elementCount = 0;
    }

    // [] operator overloading
    V& operator[](K key) {
        int index = hash(key);

        LinkedListNode<HashNode<K,V>>* current = table[index].head;
        while (current != nullptr) {
            if (current->data.key == key) {
                return current->data.value;
            }
            current = current->next;
        }

        // Key doesn't exist, insert new node
        table[index].push_back(HashNode<K,V>(key, V()));
        elementCount++;
        return table[index].tail->data.value;
    }
};

#endif //HASHTABLE_H