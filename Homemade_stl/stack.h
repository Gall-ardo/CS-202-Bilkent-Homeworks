#ifndef STACK_H
#define STACK_H

template<typename T>
struct StackNode {
    T data;
    StackNode* next;
    StackNode(const T& data) : data(data), next(nullptr) {}
};

template<typename T>
class Stack {
private:
    StackNode<T>* topNode;

public:
    Stack() : topNode(nullptr) {}
    ~Stack() { clear(); }

    void push(const T& data) {
        StackNode<T>* newNode = new StackNode<T>(data);
        newNode->next = topNode;
        topNode = newNode;
    }

    T pop() { // pop and peek works together
        if (topNode == nullptr) return T();
        StackNode<T>* poppedNode = topNode;
        T data = poppedNode->data;
        topNode = poppedNode->next;
        delete poppedNode;
        return data;
    }

    bool isEmpty() const { return topNode == nullptr; }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    T top() const {
        if (topNode == nullptr) return T();
        return topNode->data;
    }
};

#endif //STACK_H