/***************************************************************************************************
    File:  minHeap.h

    Description:
        A min heap class to define all methods and functions that enabled the main features of
        a min heap. A min heap is a tree data structure in which the tree is a complete binary
        tree. Elements found in a min heap are arranged by their priority values. Element at
        the root of a min heap must have a priority value less or equal to the rest of elements.
        A min heap is easy to element using the data structure of a priority queue. Since the
        queue was based on a single-link-list, the min heap will not actually look like a tree
        since each node only has a child. The min-heap in this implementation is a psuedo-tree.
        Example
                     0           1                 2                3                  4
        Min-Heap: [root] -> [Left child1] -> [Right child1] -> [Left child2] -> [Right child 2]

***************************************************************************************************/
#ifndef PQ
#define PQ

template <typename T>
class min_heap {
  // priority-queue-based min-heap

    private:
        size_t _capacity;                     // capacity of the queue
        size_t _size;                         // amount of data is in the queue
        int (*_cmp)(const T &, const T &);    // comparison function _cmp to assign priority value
        T *_data;                             // data pointer

        // wih the data at the given node index, return its parent's node index
        size_t _parent(size_t k);

        // with the data at the given node index, return the index of its left child
        size_t _left_child(size_t k);

        // with the data at the given node index, return the index of its right child
        size_t _right_child(size_t k);

        // swapping the data between two queue nodes
        void _swap(size_t x, size_t y);

        // helper function to rearrange the last element up the queue
        // until the queue is sorted by the elements' priority values
        void _reheap_up(size_t k);

        // helper function rearrange rearrange the top element down the queue
        // until the queue is sorted by the elements' priority values
        void _reheap_down(size_t k);

        // double the capacity of the queue, while keeping all
        // the data of the original.
        void _grow();

    public:

        // initialize a priority-queue-based min-heap and its properties
        min_heap(int (*cmp)(const T &, const T &));

        // add new item to the queue
        void add(const T & item);

        // remove the root/top element of the queue
        void remove();

        // return the data of the element at the root/top from the queue
        T front() const;

        // return the size of the queue
        size_t size() const;

};

#include "minHeap.cc"

#endif
