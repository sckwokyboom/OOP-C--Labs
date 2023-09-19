#ifndef LINKED_HASH_SET_HPP
#define LINKED_HASH_SET_HPP

#include "linked_hash_set.h"
#include <algorithm>

using namespace linkedhs;
template<class T, class Hasher>
using const_iterator = typename std::list<T>::const_iterator;

template<class T, class Hasher>
Linked_hash_set<T, Hasher>::Linked_hash_set():
        size_(0),
        capacity_(DEFAULT_CAPACITY),
        array_(new std::list<const_iterator> *[DEFAULT_CAPACITY]()) {}

template<class T, class Hasher>
Linked_hash_set<T, Hasher>::~Linked_hash_set() {
    for (unsigned int i = 0; i < capacity_; ++i) {
        delete array_[i];
    }
    delete[] array_;
}

template<class T, class Hasher>
Linked_hash_set<T, Hasher>::Linked_hash_set(const Linked_hash_set &other)
        : size_(other.size_),
          capacity_(DEFAULT_CAPACITY),
          array_(new std::list<const_iterator> *[capacity_]()) {

    // Recalculation the history and the hash set.
    for (const T &el: other.history_) {
        insert(el);
    }
}

template<class T, class Hasher>
Linked_hash_set<T, Hasher> &Linked_hash_set<T, Hasher>::operator=(Linked_hash_set other) {
    this->swap(other);
    return *this;
}

template<class T, class Hasher>
std::list<typename std::list<T>::const_iterator> *&
Linked_hash_set<T, Hasher>::get_list(const T &el) const {
    long long index = h_(el) % capacity_;
    return array_[index];
}

template<class T, class Hasher>
typename std::list<typename std::list<T>::const_iterator>::const_iterator
Linked_hash_set<T, Hasher>::find_in_list(std::list<const_iterator> *list, const T &el) const {
    return std::find_if(list->begin(), list->end(), [&el](const_iterator & it) { return *it == el; });
}

template<class T, class Hasher>
bool Linked_hash_set<T, Hasher>::insert(const T &el) {
    if (RESIZE_THRESHOLD <= (float) size_ / capacity_) {
        rehash();
    }
    std::list<const_iterator> *&list = get_list(el);
    if (list == nullptr) {
        list = new std::list<const_iterator>();
    }
    if (list->end() != find_in_list(list, el)) {
        return false;
    }
    // Push the history const_iterator in the hashset.
    const auto it = history_.insert(history_.end(), el);
    list->emplace_back(it);
    size_++;
    return true;
}

template<class T, class Hasher>
void Linked_hash_set<T, Hasher>::rehash() {
    std::list<T> prev_history = std::move(history_);
    clear();
    delete[] array_;

    capacity_ *= 2;
    array_ = new std::list<const_iterator> *[capacity_]();
    for (const auto &el: prev_history) {
        insert(el);
    }
}

template<class T, class Hasher>
bool Linked_hash_set<T, Hasher>::remove(const T &el) {
    std::list<const_iterator> *&list = get_list(el);
    if (list == nullptr || list->empty())
        return false;

    // Get the history const_iterator and remove it from hashset and history.
    auto list_it = find_in_list(list, el);
    if (list_it == list->end()) {
        return false;
    } else {
        history_.erase(*list_it);
        list->erase(list_it);
        size_--;
        return true;
    }
}

template<class T, class Hasher>
void Linked_hash_set<T, Hasher>::swap(Linked_hash_set<T, Hasher> &other) {
    std::swap(array_, other.array_);
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
    std::swap(history_, other.history_);
}

template<class T, class Hasher>
size_t Linked_hash_set<T, Hasher>::size() const {
    return size_;
}

template<class T, class Hasher>
bool Linked_hash_set<T, Hasher>::empty() const {
    return size_ == 0;
}

template<class T, class Hasher>
bool Linked_hash_set<T, Hasher>::contains(const T &t) const {
    return find(t) != end();
}

template<class T, class Hasher>
void Linked_hash_set<T, Hasher>::print() const {
    for (unsigned int i = 0; i < capacity_; ++i) {
        std::cout << i << ": ";
        if (array_[i] != nullptr) {
            for (auto it = array_[i]->begin(); it != array_[i]->end(); it++) {
                std::cout << (*it)->age_ << " " << (*it)->name_ << " -> ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << size_ << " \\ " << capacity_ << std::endl;
}

template<class T, class Hasher>
bool Linked_hash_set<T, Hasher>::operator==(Linked_hash_set<T, Hasher> &other) {
    if (size_ != other.size_)
        return false;
    for (const T &el: other) {
        if (!contains(el))
            return false;
    }
    return true;
}

template<class T, class Hasher>
bool Linked_hash_set<T, Hasher>::operator!=(Linked_hash_set<T, Hasher> &other) {
    return !(*this == other);
}

template<class T, class Hasher>
const_iterator<T, Hasher> Linked_hash_set<T, Hasher>::find(const T &el) const {
    std::list<const_iterator> *&list = get_list(el);
    if (list == nullptr) {
        return end();
    }
    const auto list_it = find_in_list(list, el);
    if (list_it == list->end()) {
        return end();
    }
    if (**list_it == el) {
        return *list_it;
    }
    return end();
}

template<class T, class Hasher>
const_iterator<T, Hasher> Linked_hash_set<T, Hasher>::begin() const {
    return history_.begin();
}

template<class T, class Hasher>
const_iterator<T, Hasher> Linked_hash_set<T, Hasher>::end() const {
    return history_.end();
}

template<class T, class Hasher>
void Linked_hash_set<T, Hasher>::clear() {
    // Clear the elements from hashset without deleting.
    for (unsigned int i = 0; i < capacity_; ++i) {
        if (array_[i] != nullptr)
            array_[i]->clear();
    }
    history_.clear();
    this->size_ = 0;
}

#endif //LINKED_HASH_SET_HPP