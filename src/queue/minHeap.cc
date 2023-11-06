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

template <typename T>
min_heap<T>::min_heap(int (*cmp)(const T &, const T &)) {
    // initialize a priority-queue-based min-heap and its properties
    _capacity = 256;               // the most the queue can store
    _size = 0;                     // size of the current queue
    _cmp = cmp;                    // function to assign priority value
    _data = new T[_capacity];
}

template <typename T>
void min_heap<T>::add(const T & item) {
    // add new item to the queue

    // add new item into the min-heap at the last slot in the queue
    _data[_size] = item;

    // reheap the new item up until the priority queue is in an increasing order
    _reheap_up(_size);
    _size++;

    // if the priority queue is out of storage,
    // grow the capacity of the queue while keeping all the data
    if (_size == _capacity) _grow();
}


template <typename T>
void min_heap<T>::remove() {
    // remove the root/top element from the queue

    // remove the top item from the queue, and replace it with
    // the last item in the queue.
    _data[0] = _data[--_size];

    // reheap the new front item down until the queue
    // is in a decrease order of priority values
    _reheap_down(0);
}


template <typename T>
T min_heap<T>::front() const {
    // return the data of the element at the root/top from the queue

    return _data[0];
}

template <typename T>
size_t min_heap<T>::size() const {
    // return the size of the queue

    return _size;
}

template <typename T>
size_t min_heap<T>::_parent(size_t k) {
    // wih the data at the given node index, return its parent's node index

    return (k - 1) / 2;
}

template <typename T>
size_t min_heap<T>::_left_child(size_t k) {
    // with the data at the given node index, return the index of its left child

    return (k * 2) + 1;
}

template <typename T>
size_t min_heap<T>::_right_child(size_t k) {
    // with the data at the given node index, return the index of its right child

    return (k * 2) + 2;
}

template <typename T>
void min_heap<T>::_swap(size_t x, size_t y) {
    // swapping the data between two queue nodes

    T temp = _data[x];
    _data[x] = _data[y];    // assign data at index x to data at index y
    _data[y] = temp;        // assign data at index y to data at index x
}

template <typename T>
void min_heap<T>::_reheap_up(size_t k) {
    // helper function to rearrange the last element up the queue
        // until the queue is sorted by the elements' priority values

    // while the value of the new item is lesser than its parents,
    // swap the parents and the new item is new item < parents
    while (k > 0 && _cmp(_data[k], _data[_parent(k)]) < 0) {
        _swap(k, _parent(k));
        k = _parent(k);
    }
}

template <typename T>
void min_heap<T>::_reheap_down(size_t k) {
    // helper function rearrange rearrange the top element down the queue
    // until the queue is sorted by the elements' priority values

    // if k is already at the bottom of the queue, stop.
    if (_left_child(k) >= _size) { return; }

    size_t child = _left_child(k);

    // find the smallest of the two childs
    if ((_right_child(k) < _size) && (_cmp(_data[_right_child(k)], _data[child]) < 0)) {
        child++;
    }

    // swap the child with the parent if child > parent, repeat until
    // the all elements in the queue are sorted by their priority values
    if (_cmp(_data[k], _data[child]) > 0) {
        _swap(k, child);
        _reheap_down(child);
    }
}

template <typename T>
void min_heap<T>::_grow() {
    // double the capacity of the queue, while keeping all
    // the data of the original.

    _capacity *= 2;                     // double the capacity
    T *bigger_copy = new T[_capacity];  // built a new bigger queue

    // copy the data original priority queue into a bigger queue
    for (size_t i = 0; i < _size; i++){
        bigger_copy[i] = _data[i];
    }

    _data = bigger_copy; // save the new bigger queue
}
