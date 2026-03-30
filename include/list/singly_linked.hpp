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
                Node(const T& element, Node* nxt = nullptr)
                : elem{element}, next{nxt} {}
        };
        int sz{0};
        Node* head{nullptr};
        Node* tail{nullptr};
    public:
        // ToDo
        SinglyLinkedList() = default; // Constructs an empty list
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
            head = new Node(elem, head);  // assign new elem as head then increase sz
            if (sz == 0) {
                tail = head;
            }
            sz++;
        }
        void pop_front() {
            Node* old{head}; // old is the current head of the list
            head = head->next;
            delete old; 
            sz--; // assign second element as new head then delete first element and reduce size
            if (sz == 0) {
                tail = nullptr;
            }
        }
        void push_back(const T& elem) {
            Node* newest{new Node(elem)}; // assign elem to next index after the tail
            if (sz == 0) {
                head = newest;
            } else {
                tail->next = newest; // assign elem as new tail
            }
            tail = newest;
            sz++;
        }
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
