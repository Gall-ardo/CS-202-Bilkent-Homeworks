/**
* Title: Heap and AVL Trees
* Author : Halil Arda Özongun
* ID: 22202709
* Section : 1
* Homework : 2
* Description : This is the header and implementation file for the Heap class. It is a min heap implementation.
*/

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;


template <typename T>
class Heap {
private:
    T* heap;
    int size; // Number of elements in the heap
    int capacity; // Maximum number of elements in the heap

    // Helper functions
    void heapify(int index);
    bool expand();
    int parent(int i);
    int left_child(int i);
    int right_child(int i);
    int findIndex(T value);

public:
    // Constructors
    Heap();
    Heap(int capacity);
    Heap(T* array, int size);
    ~Heap();
    bool isEmpty();
    void insert(T value);
    T extractTop();
    T top();// without removing
    int getSize();
    void clear();
    void remove(int i);
    void getLeast5(int* arr, int& s);
    // Equal operator to copy the heap to another heap
    //Heap<T>& operator=(const Heap<T>& other);
};


//  findIndex  operator= functions are not implemented
template<typename T>
int Heap<T>::parent(int i) {
    return (i-1)/2;
}

template<typename T>
int Heap<T>::left_child(int i) {
    return (2*i + 1);
}

template<typename T>
int Heap<T>::right_child(int i) {
    return (2*i + 2);
}

template<typename T>
void Heap<T>::heapify(int index){
    int lc = left_child(index);
    int rc = right_child(index);
    int smallest = index;
    if(lc < size && heap[lc] < heap[smallest]){
        smallest = lc;
    }
    if(rc < size && heap[rc] < heap[smallest]){
        smallest = rc;
    }
    if(smallest != index){
        T temp = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = temp;
        heapify(smallest);
    }

}

template<typename T>
Heap<T>::Heap() {
    // Default constructor
    this->capacity = 8;
    this->size = 0;
    this->heap = new T[capacity];
}

template<typename T>
Heap<T>::Heap(int capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->heap = new T[capacity];
}

template<typename T>
Heap<T>::Heap(T *array, int size) {
    // check if heap is currently empty or not
    if(size != 0){
        clear(); // clear the heap
    }

    this->capacity = size * 2;
    this->size = size;
    this->heap = new T[capacity];
    for (int i = 0; i < size; i++) {
        heap[i] = array[i];
    }
    for (int i = size / 2; i >= 0; i--) {
        heapify(i);
    }

}

template<typename T>
Heap<T>::~Heap() {
    clear();
}

template<typename T>
bool Heap<T>::isEmpty() {
    return size == 0;
}

template<typename T>
void Heap<T>::insert(T value) {
    if (size == capacity) {
        expand();
    }
    if (size == 0) {
        heap[0] = value;
        size++;
    } else {
        heap[size] = value;
        size++;
        heapify(size - 1);
    }
}

template<typename T>
// assuming the heap is not empty
T Heap<T>::top() {
    return heap[0];
}

template<typename T>
// assuming the heap is not empty
T Heap<T>::extractTop() {
    T top = heap[0];
    heap[0] = heap[size - 1];
    size--;
    heapify(0);
    return top;
}

template<typename T>
int Heap<T>::getSize() {
    return size;
}

template<typename T>
void Heap<T>::clear() {
    delete[] heap;
    heap = nullptr;
    size = 0;
    capacity = 0;
}

template<typename T>
void Heap<T>::remove(int i) {
    // find index of the element
    int index = findIndex(i);
    // change it with the last element
    heap[index] = heap[size - 1];
    size--;
    // heapify
    heapify(index);
}

template<typename T>
int Heap<T>::findIndex(T value) {
    // Implement in (nlogn) time. Temporarily O(n) solution
    for (int i = 0; i < size; i++) {
        if (heap[i] == value) {
            return i;
        }
    }
    return -1;
}
/*
template<typename T>
Heap<T> &Heap<T>::operator=(const Heap<T> &other) {
}*/

template<typename T>
bool Heap<T>::expand() {
    Heap<T> newHeap(capacity * 2);
    for (int i = 0; i < size; i++) {
        newHeap.insert(heap[i]);
    }
    delete[] heap;
    heap = newHeap.heap;
    capacity = newHeap.capacity;
    return true;
}

/* may be memory leak*/
template<typename T>
void Heap<T>::getLeast5(int *arr, int &s) {
    // if size is less than 5 give size as -1
    // if size is greater than 5 give size as 5
    /*if(this->size == 0){
        s = -1;
        return;
    }
    if(this->size < 5){
        s = this->size;
    }else{
        size = 5;
    }*/
    s = 5;


    int it = 0;
    while (it < 5 && it < size) {
        int c_index = 0;
        while (heap[it] > arr[c_index] && c_index < 5) {
            c_index++;
        }
        // now you find the index where you want to insert the element.
        // shift to the right and insert the element
        for (int i = 4; i > c_index; i--) {
            arr[i] = arr[i - 1];
        }
        arr[c_index] = heap[it];
        it++;
    }
    /* now arr contains the 5 smallest elements in the heaps first 5 elements*/
    // check until first 32 element. if you see sth smaller insert in sorted order
    while (it < 32 && it < size) {
        int c_index = 0;
        while (heap[it] > arr[c_index] && c_index < 5) {
            c_index++;
        }
        // now you find the index where you want to insert the element.
        // shift to the right and insert the element
        if(c_index == 5){
            it++;
            continue;
        }

        for (int i = 4; i > c_index; i--) {
            arr[i] = arr[i - 1];
        }
        arr[c_index] = heap[it];
        it++;
    }
}

#endif //HEAP_H
