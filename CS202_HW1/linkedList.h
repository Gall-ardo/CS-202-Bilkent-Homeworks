/**
* Title: Binary Search Trees
* Author : Halil Arda Özongun
* ID: 22202709
* Section : 1
* Homework : 1
* Description : This is a template class for pointer based linked list implementation, it has push_front, push_back,
* pop_front, pop_back, empty, get_size, clear, reverse functions.
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

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

#endif // LINKEDLIST_H