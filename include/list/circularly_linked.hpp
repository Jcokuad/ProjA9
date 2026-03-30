#pragma once

#include <utility>     // provides std::swap

namespace dsac::list {

/// circularly linked list
template <typename T>
class CircularlyLinkedList {
    private:
        class Node {
            public:
                T elem;
                Node* next;
                // ToDo
                Node(const T& element, Node* nxt = nullptr)
                : elem{element}, next{nxt} {}
        };
    private:
        int sz{0};
        Node* tail{nullptr};
    public:
        // ToDo
        CircularlyLinkedList() = default; // constructs an empty list
        int size() const {
            return sz;
        }
        bool empty() const {
            return sz == 0;
        }
        T& front() {
            return head->elem; // Returns first element at head index
        }
        const T& front() const {
            return head->elem;
        }
        T& back() {
            return tail->elem; // return last element at tail index
        }
        const T& back() const {
            return tail->elem;
        }
        void push_front(const T& elem) {
            if (sz == 0) {
                tail = new Node(elem);
                tail->next = tail;
            } else {
                tail->next = new Node(elem, tail->next);
            }
            sz++;
        }
        void push_back(const T& elem) {
            push_front(elem);
            tail = tail->next;
        }
        void pop_front() {
            Node* head = tail->next;
            if (head == tail) { // if size == 1
                tail = nullptr;
            } else {  // size > 1
                tail->next = head->next;
            }
            delete head; 
            sz--;
        }
        void rotate() {   // rotates first element to the back of the list 
            if (tail != nullptr) {
                tail = tail->next;
            }
        }

        // Split *this into two circular lists A and B, each with half the nodes.
        // Precondition: sz is even. After the call, *this becomes empty and
        // A and B each point to one of the two halves.
        void splitEven(CircularlyLinkedList& A, CircularlyLinkedList& B) {
            // If the list is empty, both result lists should also be empty
            if (empty()) {
                return;
            }
            // splitEven is only valid for even-sized lists else throw exception
            if (sz % 2 != 0) {
                throw std::runtime_error("splitEven only valid for even-sized lists");
            }
            int half = sz / 2;
            // head is the first node in the circular list
            Node* head = tail->next;

            // Find the last node of the first half
            Node* tail_first = head;
            for (int i = 1; i < half; i++) {
                tail_first = tail_first->next;
            }

            // The node after firstTail is the head of the second half

            // The original tail becomes the tail of the second half

            // Rewire pointers to form two separate circular lists
            
            // Clear destination lists first
            
            // Assign the two halves

            // Original list becomes empty
        }

    private:
        void clone(const CircularlyLinkedList& other) {
            Node* walk = other.tail;
            for (int i{0}; i < other.size(); i++) {
                push_back(walk->next->elem);
                walk = walk->next;
            }
        }
    public:
        friend void swap(CircularlyLinkedList& a, CircularlyLinkedList& b) {
            std::swap(a.sz, b.sz);
            std::swap(a.tail, b.tail);
        }
        void clear() {
            while (sz > 0) {
                pop_front();
            }
        }
        CircularlyLinkedList(const CircularlyLinkedList& other) { // copy constructor
            clone(other);
        }
        CircularlyLinkedList& operator=(const CircularlyLinkedList& other) { // copy assignment
            if (this != &other) {
                clear();
                clone(other);
            }
            return *this;
        }
        CircularlyLinkedList(CircularlyLinkedList&& other) { // move constructor
            swap(*this, other)
        }
        CircularlyLinkedList& operator=(CircularlyLinkedList&& other) { // move assignment
            if (this != other) {
                swap(*this, other);
            }
            return *this;
        }
        ~CircularlyLinkedList() {  // destructor
            clear();
        }
        void print() {
            if (tail == nullptr) {
                std::cout << "List is empty.\n";
                return;
            }

            Node* curr = tail->next;
            do {
                std::cout << curr->elem << " ";
                curr = curr->next;
            } while (curr != tail->next);

            std::cout << std::endl;
        }
};

}  // namespace dsac::list

