#ifndef LINKED_HASH_SET_H
#define LINKED_HASH_SET_H
#include <iostream>
#include <utility>
#include <vector>
#include <list>

namespace linkedhs {
    template <class T, class Hasher = std::hash<T>>
    class Linked_hash_set {
    public:
        using const_iterator = typename std::list<T>::const_iterator;

        Linked_hash_set();

        ~Linked_hash_set();

        // Create a new hashset and copy elements into it.
        Linked_hash_set(const Linked_hash_set &other);

        // Assign other hashset to the target with the same element order.
        Linked_hash_set &operator=(Linked_hash_set other);

        // Return true, if the inserting process into hashset was successful.
        // Return false, if there is an attempt to insert the already exist elements.
        bool insert(const T &e);

        // Return true, if the element was successfully removed.
        // Return false, if there is an attempt to remove the non exist elements;
        bool remove(const T &t);

        void swap(Linked_hash_set &other);

        // Get the count of unique elements in the hashtable.
        size_t size() const;

        // Return true, if the hashtable does not have any elements. Otherwise, false.
        bool empty() const;

        // Return true, if the element contains in the hashtable. Otherwise, false.
        bool contains(const T &t) const;

        // Return true, if all elements are equal, regardless of the insertion order. Otherwise, false.
        bool operator==(Linked_hash_set &other);

        bool operator!=(Linked_hash_set &other);

        // Iterates in insertion order.

        // Searches for the given element. Returns end() if not found, otherwise returns iterator for element inside the set.
        // Return the iterator that points to the given element. Otherwise, return the hashtable.end().
        const_iterator find(const T &t) const;

        // Return the iterator, pointing to the first added element in the hashtable.
        const_iterator begin() const;

        // Return the iterator, pointing to the next one after the last added element in the hashtable.
        const_iterator end() const;

        // Remove all elements in the hashset.
        void clear();

        void print() const;


    private:
        // Auxiliary struct to contain the iterator pointer and the element in the hashtable.
        void rehash();
        std::list<typename std::list<T>::const_iterator> *&get_list(const T &el) const;
        typename std::list<typename std::list<T>::const_iterator>::const_iterator
            find_in_list(std::list<const_iterator> *list, const T &el) const ;
        static constexpr float RESIZE_THRESHOLD = 0.75;
        static const int DEFAULT_CAPACITY = 16;

        unsigned int size_;
        unsigned int capacity_;

        std::list<T> history_;
        std::list<const_iterator> **array_;
        Hasher h_;
    };

}
#endif //LINKED_HASH_SET_H