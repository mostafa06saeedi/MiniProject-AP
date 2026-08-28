#include "CircularDoublyLinkedList.h"
using namespace std;
namespace CounterStrike {

CircularDoublyLinkedList::CircularDoublyLinkedList() : head(nullptr), size(0) {}

CircularDoublyLinkedList::~CircularDoublyLinkedList() {
    if (!head) return;

    Node* current = head;
    do {
        Node* temp = current;
        current = current->next;
        delete temp;
    } while (current != head);

    head = nullptr;
    size = 0;
}

void CircularDoublyLinkedList::add(int value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;
        head->next = head;
        head->prev = head;
    } else {
        Node* tail = head->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = head;
        head->prev = newNode;
    }
    size++;
}

void CircularDoublyLinkedList::remove(int value) {
    if (!head) return;

    Node* current = head;
    do {
        if (current->data == value) {
            if (current->next == current) {
                delete current;
                head = nullptr;
            } else {
                Node* prevNode = current->prev;
                Node* nextNode = current->next;
                prevNode->next = nextNode;
                nextNode->prev = prevNode;
                if (current == head) {
                    head = nextNode;
                }
                delete current;
            }
            size--;
            return;
        }
        current = current->next;
    } while (current != head);
}

void CircularDoublyLinkedList::print() const {
    if (!head) {
        cout << "List is empty." << std::endl;
        return;
    }

    Node* current = head;
    do {
        std::cout << current->data << " ";
        current = current->next;
    } while (current != head);
    std::cout << std::endl;
}

int CircularDoublyLinkedList::calculateTotalPower() const {
    if (!head) return 0;

    int totalPower = 0;
    Node* current = head;
    do {
        totalPower += current->data;
        current = current->next;
    } while (current != head);

    return totalPower;
}

int CircularDoublyLinkedList::getSize() const {
    return size;
}

} 
