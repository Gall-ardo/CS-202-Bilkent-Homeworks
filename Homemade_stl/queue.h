#ifndef QUEUE_H
#define QUEUE_H

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

#endif // QUEUE_H