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
        void splitEven(CircularlyLinkedList& A, CircularlyLinkedList& B);
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

