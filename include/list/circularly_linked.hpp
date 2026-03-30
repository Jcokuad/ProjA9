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
                Node(const T& element, Node* nxt = nullptr);
        };
    private:
        int sz{0};
        Node* tail{nullptr};
    public:
        // ToDo
        CircularlyLinkedList();
        int size() const;
        bool empty() const;
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;
        void push_front(const T& elem);
        void push_back(const T& elem);
        void pop_front();
        void rotate();

        // Split *this into two circular lists A and B, each with half the nodes.
        // Precondition: sz is even. After the call, *this becomes empty and
        // A and B each point to one of the two halves.
        void splitEven(CircularlyLinkedList& A, CircularlyLinkedList& B) {
            // If the list is empty, both result lists should also be empty

            // splitEven is only valid for even-sized lists else throw exception

            // head is the first node in the circular list

            // Find the last node of the first half

            // The node after firstTail is the head of the second half

            // The original tail becomes the tail of the second half

            // Rewire pointers to form two separate circular lists
            
            // Clear destination lists first
            
            // Assign the two halves

            // Original list becomes empty
        }
        
    private:
        void clone(const CircularlyLinkedList& other);
    public:
        friend void swap(CircularlyLinkedList& a, CircularlyLinkedList& b);
        void clear();
        CircularlyLinkedList(const CircularlyLinkedList& other);
        CircularlyLinkedList& operator=(const CircularlyLinkedList& other);
        CircularlyLinkedList(CircularlyLinkedList&& other);
        CircularlyLinkedList& operator=(CircularlyLinkedList&& other);
        ~CircularlyLinkedList();
        void print();
};

}  // namespace dsac::list

