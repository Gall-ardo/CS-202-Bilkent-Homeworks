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

    /*T& front() {
        if (empty()) throw std::out_of_range("List is empty");
        return head->data;
    }

    const T& front() const {
        if (empty()) throw std::out_of_range("List is empty");
        return head->data;
    }

    T& back() {
        if (empty()) throw std::out_of_range("List is empty");
        return tail->data;
    }

    const T& back() const {
        if (empty()) throw std::out_of_range("List is empty");
        return tail->data;
    }*/

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

    // Iterator support
    /*class iterator {
    private:
        LinkedListNode<T>* current;
    public:
        iterator(LinkedListNode<T>* node) : current(node) {}
        T& operator*() { return current->data; }
        iterator& operator++() { current = current->next; return *this; }
        bool operator!=(const iterator& other) { return current != other.current; }
    };

    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }*/
};

#endif // LINKEDLIST_H