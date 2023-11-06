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

template <typename T>
priority_queue<T>::priority_queue(int (*cmp)(const T &, const T &)) {
    // Initialize a priority queue

    _front = NULL;
    _size = 0;
    _cmp = cmp;
}

template <typename T>
priority_queue<T>::node::node(const T & item, node * rest)  // Initalize an element in queue
    : data(item), next(rest) {}

template <typename T>
void priority_queue<T>::_add_helper(const T & item, node * & lst) {
    // Queueu management helper to rearrange elements using priority values

    if (lst == NULL)
        lst = new node(item, NULL);
    else if (_cmp(item, lst->data) <= 0)
        lst = new node(item, lst);
    else _add_helper(item, lst->next);
}

template <typename T>
void priority_queue<T>::add(const T & item) {
    // Add element to a priority queue

    _add_helper(item, _front);
    _size++;
}

template <typename T>
void priority_queue<T>::remove() {
    // Remove element from queue

    node * dead = _front;
    _front = _front->next;
    delete dead;
    _size--;
}

template <typename T>
T priority_queue<T>::front() const {
    // Return the data of element with highest priority value in queue

    return _front->data;
}

template <typename T>
size_t priority_queue<T>::size() const {
    // Return the size of the queue

    return _size;
}
