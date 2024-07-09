#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <stdexcept>

// Forward declaration for the template class
template <typename T>
class List {
public:
    List();
    List(const List<T>& other) : head(nullptr), tail(nullptr), list_size(0)
    {
        copyFrom(other);
    } // Copy constructor
    List<T>& operator=(const List<T>& other)
    {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }
    ~List();

    void push_back(const T& element);
    void push_front(const T& element);
    void pop_back();
    void pop_front();
    bool empty() const;
    size_t size() const;
    void remove(const T& element);
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    class iterator;
    iterator begin();
    iterator end();
    void clear();
    void copyFrom(const List<T>& other)
    {
        for (Node* node = other.head; node != nullptr; node = node->next) {
            push_back(node->data);
        }
    }

private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& d);
    };

    Node* head;
    Node* tail;
    size_t list_size;
    Node* getNode(size_t index) const;


};

// Iterator class
template <typename T>
class List<T>::iterator {
public:
    iterator(Node* node = nullptr);

    iterator& operator++();
    iterator& operator--();
    T& operator*();
    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;

private:
    Node* current;
};

// Include the implementation in the header for simplicity
//#include "List_impl.h"

#endif // LIST_H
