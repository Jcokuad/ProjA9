#pragma once

#include <utility>     // provides std::swap

namespace dsac::list {
//akin to std::list
template <typename T>
class DoublyLinkedList {
    private:
        class Node {
            public:
                T elem;
                Node* prev{nullptr};
                Node* next{nullptr};
                
                // ToDo
                Node();
                Node(const T& element, Node* prv, Node* nxt);
        };
        int sz{0};
        Node* header; // sentinel node
        Node* trailer;// sentinel node
        void create_sentinels();
    public:
        // ToDo
        DoublyLinkedList();
        int size() const;
        bool empty() const;
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;
    private:
        Node* insert_before(T elem, Node* successor);
        void erase(Node* node);
    public:
        void push_front(const T& elem);
        void push_back(const T& elem);
        void pop_front();
        void pop_back();
        void concatenate(DoublyLinkedList& M);
    public:
        class iterator {
            friend class DoublyLinkedList;
            private:
                Node* node_ptr;
            public:
                iterator(Node* ptr = nullptr);
                T& operator*() const;
                T* operator->() const;
                iterator& operator++();
                iterator operator++(int);
                iterator& operator--();
                iterator operator--(int);
                bool operator==(const iterator& other) const;
                bool operator!=(const iterator& other) const;
        };
        class const_iterator {
            private:
                const Node* node_ptr;
            public:
                const_iterator(const Node* ptr = nullptr);
                const T& operator*() const;
                const T* operator->() const;
                const_iterator& operator++();
                const_iterator operator++(int);
                const_iterator& operator--();
                const_iterator operator--(int);
                bool operator==(const const_iterator& other) const;
                bool operator!=(const const_iterator& other) const;
        };

    public:
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
        iterator insert(iterator it, const T& elem);
        iterator erase(iterator it);
    private:
        void clone(const DoublyLinkedList& other);
    public:
        friend void swap(DoublyLinkedList& a, DoublyLinkedList& b);
        void clear();
        DoublyLinkedList(const DoublyLinkedList& other);
        DoublyLinkedList& operator=(const DoublyLinkedList& other);
        DoublyLinkedList(DoublyLinkedList&& other);
        DoublyLinkedList& operator=(DoublyLinkedList&& other);
        ~DoublyLinkedList();
        void print() const;
};
}  // namespace dsac::list
