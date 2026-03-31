#pragma once

#include <utility>     // provides std::swap
#include <stdexcept>
#include <iostream>

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
            if (empty()) {
                throw std::out_of_range("pop_front on empty list");
            }
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
        void concatenate(SinglyLinkedList& M) {
            // self-concatenation: do nothing
            if (this == &M) {
                return;
            }
            // nothing to add if M is empty
            if (M.empty()) {
                return;
            }
            // current list is empty: adopt M in complete
            if (empty()) {
                head = M.head;
                tail = M.tail;
                sz = M.sz;
            }
            // general splice: tail -> M.head, then adopt M.tail
            else {
                tail->next = M.head;
                tail = M.tail;
                sz += M.sz;
            }
            // reset M to empty state
            M.head = nullptr;
            M.tail = nullptr;
            M.sz = 0;
        }

        // Reverse the singly linked list in-place, using O(1) extra space.
        // After this, head and tail are swapped, and all links are reversed.
        void reverse() {
            // nothing to do for empty or single-node list
            if (sz <= 1) {
                return;
            }
            // Traverse the list and reverse links one by one
            Node* prev = nullptr;
            Node* curr = head;
            Node* old = head;

            while (curr != nullptr) {
                Node* next = curr->next; // store the next node
                curr->next = prev;
                prev = curr;    // move the current and previous forward
                curr = next;    
            }

            head = prev;    // head and tail are swapped 
            tail = old;
        }
    public:
        class iterator {
            friend class SinglyLinkedList;
            private:
                Node* node_ptr;  // pointer to a node
            public:
                // ToDo
                iterator(Node* ptr = nullptr) : node_ptr(ptr) {} 
                T& operator*() const {
                    return node_ptr->elem;
                }
                T* operator->() const {
                    return &node_ptr->elem;
                }
                iterator& operator++() {
                    node_ptr = node_ptr->next;
                    return *this;
                }
                iterator operator++(int) {
                    iterator temp(*this);
                    ++(*this);
                    return temp;
                }
                bool operator==(iterator rhs) const {
                    return node_ptr == rhs.node_ptr;
                }
                bool operator!=(iterator rhs) const {
                    return node_ptr != rhs.node_ptr;
                }
        };
    public:
        class const_iterator {
            private:
                Node* node_ptr;
            public:
                const_iterator(Node* ptr = nullptr) : node_ptr(ptr) {}
                const T& operator*() const {
                    return node_ptr->elem;
                }
                const T* operator->() const {
                    return &node_ptr->elem;
                }
                const_iterator& operator++() {
                    node_ptr = node_ptr->next;
                    return *this;
                }
                const_iterator operator++(int) {
                    const_iterator temp(*this);
                    ++(*this);
                    return temp;
                }
                bool operator==(const_iterator rhs) const {
                    return node_ptr == rhs.node_ptr;
                }
                bool operator!=(const_iterator rhs) const {
                    return node_ptr != rhs.node_ptr;
                }
        };
    public:
        iterator begin() {
            return iterator(head);
        }
        const_iterator begin() const {
            return const_iterator(head);
        }
        iterator end() {
            return iterator(nullptr);
        }
        const_iterator end() const {
            return const_iterator(nullptr);
        }
        iterator insert_after(iterator it, const T& elem) {
            if (it.node_ptr == nullptr) {
                throw std::out_of_range("Invalid iterator");
            }
            it.node_ptr->next = new Node(elem, it.node_ptr->next);
            // newest node becomes tail
            if (tail == it.node_ptr) {
                tail = it.node_ptr->next;
            }
            sz++;
            return iterator(it.node_ptr->next);
        }
        iterator erase_after(iterator it) {
            if (it.node_ptr == nullptr || it.node_ptr->next == nullptr) {
                throw std::out_of_range("Invalid iterator");
            }
            Node* after = it.node_ptr->next;
            // old tail is removed
            if (tail == after) {
                tail = it.node_ptr;
            }
            it.node_ptr->next = after->next;
            delete after;
            sz--;
            // return iterator to what newly follows the original iterator
            return iterator(it.node_ptr->next);
        }
    
    // RULE-OF-FIVE Implementation
    private:
        void clone(const SinglyLinkedList& other) {
            for (T elem : other) {  // add each element of other to the list
                push_back(elem);
            }
        }
    public:
        // non-member function to swap two lists
        friend void swap(SinglyLinkedList& a, SinglyLinkedList& b) {
            std::swap(a.sz, b.sz);
            std::swap(a.head, b.head);
            std::swap(a.tail, b.tail);
        }
        void clear() {
            while (sz > 0) {
                pop_front();
            }
        }
        SinglyLinkedList(const SinglyLinkedList& other) {  // copy constructor
            clone(other);
        }
        SinglyLinkedList& operator=(const SinglyLinkedList& other) { // copy assignment
            if (this != &other) {
                clear();
                clone(other);
            }
            return *this;
        }
        SinglyLinkedList(SinglyLinkedList&& other) {  // move constructor
            swap(*this, other);
        }
        SinglyLinkedList& operator=(SinglyLinkedList&& other) { // move assignment
            if (this != &other) {
                swap(*this, other);
            }
            return *this;
        }
        ~SinglyLinkedList() { // destructor
            clear();
        }
};

} // namespace dsac::list
