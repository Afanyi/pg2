#ifndef LIST_IMPL_H
#define LIST_IMPL_H

#include "List.h"

// Node constructor
template <typename T>
List<T>::Node::Node(const T& d) : data(d), prev(nullptr), next(nullptr) {}

// List constructors and destructor
template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), list_size(0) {}

template <typename T>
List<T>::~List() {
    clear();
}

// List member functions
template <typename T>
void List<T>::push_back(const T& element) {
    Node* newNode = new Node(element);
    if (tail) {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    } else {
        head = tail = newNode;
    }
    list_size++;
}

template <typename T>
void List<T>::push_front(const T& element) {
    Node* newNode = new Node(element);
    if (head) {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    } else {
        head = tail = newNode;
    }
    list_size++;
}

template <typename T>
void List<T>::pop_back() {
    if (tail) {
        Node* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        list_size--;
    } else {
        throw std::underflow_error("List is empty");
    }
}

template <typename T>
void List<T>::pop_front() {
    if (head) {
        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        list_size--;
    } else {
        throw std::underflow_error("List is empty");
    }
}

template <typename T>
bool List<T>::empty() const {
    return list_size == 0;
}

template <typename T>
size_t List<T>::size() const {
    return list_size;
}

template <typename T>
void List<T>::remove(const T& element) {
    Node* current = head;
    while (current) {
        if (current->data == element) {
            Node* temp = current;
            if (current->prev)
                current->prev->next = current->next;
            else head = current->next;
            if (current->next)
                current->next->prev = current->prev;
            else tail = current->prev;
                current = current->next;
            delete temp;
            list_size--;
        } else {
            current = current->next;
        }
    }
}

template <typename T>
void List<T>::clear() {
    while (head) {
        pop_front();
    }
}

// Iterator constructors and member functions
template <typename T>
List<T>::iterator::iterator(Node* node) : current(node) {}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++() {
    if (current) {
        current = current->next;
    }
    return *this;
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator--() {
    if (current) {
        current = current->prev;
    } else {
        throw std::out_of_range("Iterator cannot be decremented");
    }
    return *this;
}

template <typename T>
T& List<T>::iterator::operator*() {
    if (current) {
        return current->data;
    } else {
        throw std::out_of_range("Dereferencing null iterator");
    }
}

template <typename T>
bool List<T>::iterator::operator==(const iterator& other) const {
    return current == other.current;
}

template <typename T>
bool List<T>::iterator::operator!=(const iterator& other) const {
    return current != other.current;
}

// List iterator functions
template <typename T>
typename List<T>::iterator List<T>::begin() {
    return iterator(head);
}

template <typename T>
typename List<T>::iterator List<T>::end() {
    return iterator(nullptr);
}

template<typename T>
T& List<T>::operator[](size_t index) {
    Node* node = getNode(index);
    return node->data;
}

template<typename T>
const T& List<T>::operator[](size_t index) const {
    Node* node = getNode(index);
    return node->data;
}

template<typename T>
typename List<T>::Node* List<T>::getNode(size_t index) const {
    if (index >= list_size) throw std::out_of_range("Index out of range");
    Node* current = head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current;
}

#endif // LIST_IMPL_H
