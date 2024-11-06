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
bool customCompare(T a, T b){
    return a < b;
}

template<typename T, typename Compare = decltype(&customCompare<T>)>
class Heap {
private:
    T* heap;
    int size; // Number of elements in the heap
    int capacity; // Maximum number of elements in the heap
    Compare compareF;

    void heapify(int index) {
        int lc = left_child(index);
        int rc = right_child(index);
        int smallest = index;

        if(lc < size && compareF(heap[lc], heap[smallest])) {
            smallest = lc;
        }
        if(rc < size && compareF(heap[rc], heap[smallest])) {
            smallest = rc;
        }
        if(smallest != index) {
            T temp = heap[index];
            heap[index] = heap[smallest];
            heap[smallest] = temp;
            heapify(smallest);
        }
    }
    bool expand() {
        T* nH = new T[capacity*2];
       for( int i = 0; i < size; i++) {
           nH[i] = heap[i];
       }
        delete[] heap;
        heap = nH;
        capacity = capacity*2;
        return true;
    }
    int parent(int i) { return (i-1)/2; }
    int left_child(int i) { return (2*i + 1); }
    int right_child(int i) { return (2*i + 2); }


public:
    Heap(Compare comp = &customCompare<T>) {
        this->compareF = comp;
        this->capacity = 1000000;
        this->size = 0;
        this->heap = new T[capacity];
    }

    Heap(int capacity, Compare comp = &customCompare<T>) {
        this->compareF = comp;
        this->capacity = capacity;
        this->size = 0;
        this->heap = new T[capacity];
    }

    // copy constructor
    Heap(const Heap& other) {
        this->compareF = other.compareF;
        this->capacity = other.capacity;
        this->size = other.size;
        this->heap = new T[capacity];

        for(int i = 0; i < size; i++) {
            heap[i] = other.heap[i];
        }
    }



    Heap(T* array, int size, Compare comp = &customCompare<T>) {
        this->compareF = comp;
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

    ~Heap() {
        delete[] heap;
        heap = nullptr;
        size = 0;
        capacity = 0;
    }

    bool isEmpty() {
        return size == 0;
    }

    void insert(T value) {
        if (size == capacity) {
            expand();
        }
        heap[size] = value;

        int current = size;
        while (current > 0 && compareF(heap[current], heap[parent(current)])) {
            T temp = heap[current];
            heap[current] = heap[parent(current)];
            heap[parent(current)] = temp;
            current = parent(current);
        }
        size++;
    }

    T extractTop() {
        if (size == 0) return T();

        T top = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapify(0);
        return top;
    }

    T top() {
        if (size == 0) return T();
        return heap[0];
    }

    int getSize() {
        return size;
    }

    void clear() {
        delete[] heap;
        heap = nullptr;
        size = 0;
        capacity = 0;
        heap = new T[capacity];
    }

    void remove(int i) {
        if (i >= size) return;

        heap[i] = heap[size - 1];
        size--;
        heapify(i);
    }

    // Returns a new array containing the elements in the heap, as sorted
    T* getHeap() {
        Heap<T, Compare> tempHeap(*this);
        T* arr = new T[size];

        for(int i = 0; i < size; i++) {
            arr[i] = tempHeap.extractTop();
        }
        return arr;
    }

    // Works in O(1) time
    void getLeast5(int* arr, int& s) {
        if(size < 5) {
            s = size;
            // For less than 5 elements, copy and sort them
            for(int i = 0; i < s; i++) {
                arr[i] = heap[i];
            }

            // Sort
            for(int i = 0; i < s - 1; i++) {
                for(int j = 0; j < s - i - 1; j++) {
                    if(!compareF(arr[j], arr[j + 1])) {  // if arr[j] > arr[j+1]
                        int temp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = temp;
                    }
                }
            }
            return;
        }

        s = 5;
        // Initialize array to store the smallest elements
        for(int i = 0; i < 5; i++) {
            arr[i] = heap[i];
        }

        // Sort initial 5
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4 - i; j++) {
                if(!compareF(arr[j], arr[j + 1])) {  // if arr[j] > arr[j+1]
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }

        // Check remaining elements
        int limit = min(32, size);
        for(int i = 5; i < limit; i++) {
            if(compareF(heap[i], arr[4])) {
                int j;
                for(j = 3; j >= 0 && compareF(heap[i], arr[j]); j--) {
                    arr[j + 1] = arr[j];
                }
                arr[j + 1] = heap[i];
            }
        }
    }



};

#endif //HEAP_H
