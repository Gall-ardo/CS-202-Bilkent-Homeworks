/**
* Title: Graphs
* Author : Halil Arda Özongun
* ID: 22202709
* Section : 1
* Homework : 4
* Description : MolGraph class header file, includes Queue and LinkedList classes.
*/

#ifndef MOLGRAPH_H
#define MOLGRAPH_H

#include <iostream>
#include <fstream>
using namespace std;

// Queue class

template<typename T>
class QueueNode {
public:
    T data;
    QueueNode* next;
    QueueNode* prev;
    QueueNode(const T& data) : data(data), next(nullptr), prev(nullptr) {}
};

template<typename T>
class Queue {
private:
    QueueNode<T>* front;
    QueueNode<T>* rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}
    ~Queue() { clear(); }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const { return size == 0; }

    int getSize() const { return size; }

    // add the element to the rear
    void push(const T& data) {
        QueueNode<T>* newNode = new QueueNode<T>(data);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            newNode->prev = rear;
            rear = newNode;
        }
        size++;
    }

    // remove the first element
    bool pop() {
        if (isEmpty()) return false;

        QueueNode<T>* temp = front;
        front = front->next;
        if (front != nullptr) {
            front->prev = nullptr;
        } else {
            rear = nullptr;
        }
        delete temp;
        size--;
        return true;
    }

    T getFront() const {
        if (front != nullptr) {
            T frontData = front->data;
            return frontData;
        } else {
            return T();
        }
    }


    T getRear() const {
        if (rear != nullptr) {
            T rearData = rear->data;
            return rearData;
        } else {
            return T();
        }
    }
};

// Linkedlist class

template<typename T>
class LinkedListNode {
public:
    T data;
    LinkedListNode* next;

    LinkedListNode(const T& data) : data(data), next(nullptr) {}
};

template<typename T>
class LinkedList {
public:
    LinkedListNode<T>* head;
    LinkedListNode<T>* tail;
    int size;

    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~LinkedList() {
        clear();
    }

    // Copy constructor
    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), size(0) {
        LinkedListNode<T>* temp = other.head;
        while (temp != nullptr) {
            push_back(temp->data);
            temp = temp->next;
        }
    }

    // Assignment operator
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            LinkedListNode<T>* temp = other.head;
            while (temp != nullptr) {
                push_back(temp->data);
                temp = temp->next;
            }
        }
        return *this;
    }

    void push_front(const T& data) {
        LinkedListNode<T>* newNode = new LinkedListNode<T>(data);
        if (empty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    void push_back(const T& data) {
        LinkedListNode<T>* newNode = new LinkedListNode<T>(data);
        if (empty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void pop_front() {
        if (!empty()) {
            LinkedListNode<T>* temp = head;
            head = head->next;
            delete temp;
            size--;
            if (empty()) {
                tail = nullptr;
            }
        }
    }

    void pop_back() {
        if (empty()) return;
        if (head == tail) {
            delete head;
            head = tail = nullptr;
            size = 0;
            return;
        }
        LinkedListNode<T>* temp = head;
        while (temp->next != tail) {
            temp = temp->next;
        }
        delete tail;
        tail = temp;
        tail->next = nullptr;
        size--;
    }

    bool empty() const {
        return size == 0;
    }

    int get_size() const {
        return size;
    }

    void clear() {
        while (head != nullptr) {
            LinkedListNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }

    // returns reverse of the list, original list is not changed
    LinkedList reverse() const {
        LinkedList reversed;
        LinkedListNode<T>* temp = head;
        while (temp != nullptr) {
            reversed.push_front(temp->data);
            temp = temp->next;
        }
        return reversed;
    }
};


class MolGraph {
private:
    // hold the graph as matrix
    int **graph;
    int numAtoms;

public:
    MolGraph(const string& filename);
    ~MolGraph();
    void minBondPath(int source, int destination);
    void getDiameter();
    void getMST();
};


#endif //MOLGRAPH_H
