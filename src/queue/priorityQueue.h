/***************************************************************************************************
    File: priorityQueue.h

    Description:
        A priority queue class to define all methods and functions that enabled the main features
        of a priority queue. A priority queue allows user to store and arrange elements based on
        the elements' priority values. Elements with higher priority values are retrievable
        before elements with lower priority values. Each element has its priority value, which is
        assigned when it was added to the queue. We use the data structure of a linked-list to
        store the data of the element in the queue. Linked-list makes it easier to manage elements
        such as by streamline the process of  adding, rearranging, and removing elements

***************************************************************************************************/
#ifndef PQ
#define PQ

template <typename T>
class priority_queue {
    private:
        // linked-list-based queue
        struct node {
            T data;                     // node data
            node *next;                 // node pointer
            node(const T &, node *);
        };

        // Comparison function _cmp to assign priority value to an element
        int (*_cmp)(const T &, const T &);

        // Pointer to keep track of the element with the highest priority value
        node *_front;

        // Size of the queue
        size_t _size;

        // Function to help rearrange element using the priority values
        void _add_helper(const T &, node * &);

    public:
        // Initialize the priority queue and its properties
        priority_queue(int (*cmp)(const T &, const T &));

        // Function to add item to queue
        void add(const T & item);

        // Function to remove item from queue
        void remove();

        // Function to get the element with highest priority queue
        T front() const;

        // Function to get the size of queue
        size_t size() const;
};

#include "priorityQueue.cc"

#endif
