#ifndef CIRCULAR_DOUBLY_LINKED_LIST_H
#define CIRCULAR_DOUBLY_LINKED_LIST_H

#include <iostream>
#include <stdexcept>

namespace CounterStrike {

class CircularDoublyLinkedList {
private:
    struct Node {
        int data;
        Node* next;
        Node* prev;

        Node(int value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    int size;

public:
    CircularDoublyLinkedList();
    ~CircularDoublyLinkedList();

    void add(int value);
    void remove(int value);
    void print() const;
    int calculateTotalPower() const;
    int getSize() const;

    class Iterator {
    private:
        Node* current;
        Node* head;

    public:
        Iterator(Node* node, Node* headNode) : current(node), head(headNode) {}

        int& operator*() { return current->data; }

        Iterator& operator++() {
            if (current)
                current = current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    Iterator begin() const { return Iterator(head, head); }
    Iterator end() const { return Iterator(nullptr, head); }
};

}

#endif
