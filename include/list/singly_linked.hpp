#pragma once

#include <utility>     // provides std::swap

namespace dsac::list {

// similar to std::forward_list
template <typename T>
class SinglyLinkedList {
    private:
        class Node {
            public:
                T elem;
                Node* next;
                // ToDo
                Node(const T& element, Node* nxt = nullptr);
        };
        int sz{0};
        Node* head{nullptr};
        Node* tail{nullptr};
    public:
        // ToDo
        SinglyLinkedList();
        int size() const;
        bool empty() const;
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;
        void push_front(const T& elem);
        void pop_front();
        void push_back(const T& elem);
        void concatenate(SinglyLinkedList& M);
        void reverse();
    public:
        class iterator {
            friend class SinglyLinkedList;
            private:
                Node* node_ptr;  // pointer to a node
            public:
                // ToDo
                iterator(Node* ptr = nullptr);
                T& operator*() const;
                T* operator->() const;
                iterator& operator++();
                iterator operator++(int);
                bool operator==(iterator rhs) const;
                bool operator!=(iterator rhs) const;
        };
    public:
        class const_iterator {
            private:
                Node* node_ptr;
            public:
                const_iterator(Node* ptr = nullptr);
                const T& operator*() const;
                const T* operator->() const;
                const_iterator& operator++();
                const_iterator operator++(int);
                bool operator==(const_iterator rhs) const;
                bool operator!=(const_iterator rhs) const;
        };
    public:
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
        iterator insert_after(iterator it, const T& elem);
        iterator erase_after(iterator it);
    private:
        void clone(const SinglyLinkedList& other);
    public:
        friend void swap(SinglyLinkedList& a, SinglyLinkedList& b);
        void clear();
        SinglyLinkedList(const SinglyLinkedList& other);
        SinglyLinkedList& operator=(const SinglyLinkedList& other);
        SinglyLinkedList(SinglyLinkedList&& other);
        SinglyLinkedList& operator=(SinglyLinkedList&& other);
        ~SinglyLinkedList();
};

} // namespace dsac::list
