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
                Node() = default;
                Node(const T& element, Node* prv, Node* nxt)
                : elem{element}, prev{prv}, next{nxt} {}
        };
        int sz{0};
        Node* header; // sentinel node
        Node* trailer;// sentinel node
        void create_sentinels() {
            header = new Node();
            trailer = new Node();
            header->next = trailer;
            trailer->prev = header;
        }
    public:
        // ToDo
        DoublyLinkedList() {
            create_sentinels();
        }
        int size() const {
            return sz;
        }
        bool empty() const {
            return sz == 0;
        }
        T& front() {
            return header->next->elem;
        }
        const T& front() const {
            return header->next->elem;
        }
        T& back() {
            return trailer->prev->elem;
        }
        const T& back() const {
            return trailer->prev->elem;
        }
    private:
        Node* insert_before(T elem, Node* successor) {
            Node* predecessor = successor->prev;
            Node* newest = new Node(elem, predecessor, successor);
            predecessor->next = newest;
            successor->prev = newest;
            sz++;
            return newest;
        }
        void erase(Node* node) {
            Node* predecessor = node->prev;
            Node* successor = node->next;
            predecessor->next = successor;
            successor->prev = predecessor;
            delete node;
            sz--;
        }
    public:
        void push_front(const T& elem) {
            insert_before(elem, header->next);
        }
        void push_back(const T& elem) {
            insert_before(elem, trailer);
        }
        void pop_front() {
            erase(header->next);
        }
        void pop_back() {
            erase(trailer->prev);
        }
        void concatenate(DoublyLinkedList& M) {
            // self-concat not allowed
            if (this = &M) {
                return;
            }
            // nothing to add if M empty
            if (M.empty()) {
                return;
            }
            // Case 1: current list (*this) is empty
            if (empty()) {
                header->next = M.header->next; // connects the header to the first elem of M
                M.header->next->prev = header;

                trailer->prev = M.trailer->prev; // connects the trailer to the last elem of M
                M.trailer->prev->next = trailer; 
                sz = M.sz;
            }
            // Case 2: both lists are non-empty
            else {
                Node* lastNode = trailer->prev;  // last node
                Node* firstM = M.header->next;   // first node in M
                Node* lastM = M.trailer->prev;   // last node in M
                
                lastNode->next = firstM; // connect this to M
                firstM->prev = lastNode;
                lastM->next = trailer;
                trailer->prev = lastM;

                sz += M.sz;
            }
            // Reset M to empty using its OWN sentinels
            M.header->next = M.trailer;
            M.trailer->prev = M.header;
            M.sz = 0;
        }
    public:
        class iterator {
            friend class DoublyLinkedList;
            private:
                Node* node_ptr;
            public:
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
                iterator& operator--() {
                    node_ptr = node_ptr->prev;
                    return *this;
                }
                iterator operator--(int) {
                    iterator temp(*temp);
                    --(*this);
                    return temp;
                }
                bool operator==(const iterator& other) const {
                    return node_ptr == other.node_ptr;
                }
                bool operator!=(const iterator& other) const {
                    return node_ptr != other.node_ptr;
                }
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

                const_iterator(const Node* ptr = nullptr) : node_ptr(ptr) {}
                const T& operator*() const {
                    return node_ptr->elem;
                }
                const T* operator->() const {
                    return &node_ptr->elem;
                }
                const_iterator& operator++() {
                    node_ptr = node_ptr->next;
                }
                const_iterator operator++(int) {
                    iterator temp(*this);
                    ++(*this);
                    return temp;
                }
                bool operator==(const const_iterator& other) const {
                    return node_ptr == other.node_ptr;
                }
                bool operator!=(const const_iterator& other) const {
                    return node_ptr != other.node_ptr;
                }
        };

    public:
        iterator begin() {
            return iterator(header->next);
        }
        const_iterator begin() const {
            return const_iterator(header->next);
        }
        iterator end() {
            return iterator(trailer);
        }
        const_iterator end() const {
            return const_iterator(trailer);
        }
        iterator insert(iterator it, const T& elem) {
            Node* node = it.node_ptr;
            Node* new_node = insert_before(elem, node);
            return iterator(new_node);
        }
        iterator erase(iterator it) {
            Node* node = it.node_ptr;
            ++it;
            erase(node);
            return it;
        }
    private:
        void clone(const DoublyLinkedList& other) {
            for (T elem : other) {
                push_back(elem);
            }
        }
    public:
        friend void swap(DoublyLinkedList& a, DoublyLinkedList& b) {
            std::swap(a.sz, b.sz);
            std::swap(a.header, b.header);
            std::swap(a.trailer, b.trailer);
        }
        void clear() {
            while (sz > 0) {
                pop_front();
            }
        }
        DoublyLinkedList(const DoublyLinkedList& other) {
            create_sentinels();  //establish as an empty list
            clone(other);       // then copy other
        }
        DoublyLinkedList& operator=(const DoublyLinkedList& other) {
            if (this != &other) {
                clear();
                clone(other);
            }
            return *this;
        }
        DoublyLinkedList(DoublyLinkedList&& other) {
            create_sentinels();  // establish as an empty list
            swap(*this, other); // then trade states with other
        }
        DoublyLinkedList& operator=(DoublyLinkedList&& other) {
            if (this != &other) {
                swap(*this, other);
            }
            return *this;
        }
        ~DoublyLinkedList() {
            clear();
            delete header;
            delete trailer;
        }
        void print() const {
            if (sz == 0) {
                std::cout << "List is empty. \n";
                return;
            }
            for (auto it = begin(); it != end(); ++it) {
                std::cout << *it << " ";
            }
            std::cout << std::endl;
        }
};
}  // namespace dsac::list
