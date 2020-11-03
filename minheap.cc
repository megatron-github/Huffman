/******************************************************************************
  
  File:  Compression.cc
 
  Description: Built a priority queue base min heap. The priority queue have
                to have properties of a min heap such as all data are stored 
                in an array and is in the an increasing order as the indexing 
                down the list. Thepriority queue allows user to build a queue, 
                get the data at the front of the queue, size of the queue, add 
                item to and remove item from the queue.

 *****************************************************************************/

template <typename T>
priority_queue<T>::priority_queue(int (*cmp)(const T &, const T &)) {
  // initialize a priority-queue-base-min-heap and its properties

  _capacity = 256;               // the most a queue can store
  _size = 0;                     // size of the current queue
  _cmp = cmp;                    // comparison function
  _data = new T[_capacity];      // minheap-base queue is an priority queue
}

template <typename T>
void priority_queue<T>::add(const T & item) {
  // add new item into queue

  // add new item into the min-heap at the last slot in the priority queue
  _data[_size] = item;

  // reheap the new item up until the priority queue is in an increasing order
  _reheap_up(_size);
  _size++;

  // if the priority queue is out of storage,
  // grow the priority queue but keeping all the data
  if (_size == _capacity) _grow();
}


template <typename T>
void priority_queue<T>::remove() {
  // remove the front item of the priority queue

  // remove the front item of the priority queue, and replace it with
  // the last item in the priority queue. (note well, pre-decrement operator!)
  _data[0] = _data[--_size];

  // reheap the new front item down until the priority queue
  // is in a decrease order
  _reheap_down(0);
}


template <typename T>
T priority_queue<T>::front() const {
  // return the first item in the priority queue

  return _data[0];
}

template <typename T>
size_t priority_queue<T>::size() const {
  // return the size of the priority queue

  return _size;
}

template <typename T>
size_t priority_queue<T>::_parent(size_t k) {
  // with the data at the given index, return its parent's index

  return (k - 1) / 2;
}

template <typename T>
size_t priority_queue<T>::_left_child(size_t k) {
  // with the data at the given index, return the index of its left child

  return (k * 2) + 1;
}

template <typename T>
size_t priority_queue<T>::_right_child(size_t k) {
  // with the data at the given index, return the index of its left child

  return (k * 2) + 2;
}

template <typename T>
void priority_queue<T>::_swap(size_t x, size_t y) {
  // swapping the values between two priority queues

  T temp = _data[x];
  _data[x] = _data[y];  // assign data at index x to data at index y
  _data[y] = temp;      // assign data at index y to data at index x
}

template <typename T>
void priority_queue<T>::_reheap_up(size_t k) {
  // helper function that move the new added item up the priority queue
  // to keep the priority queue in a increase order

  // while the value of the new item is lesser than its parents
  while (k > 0 && _cmp(_data[k], _data[_parent(k)]) < 0) {

    // swap the parents and the new item is new item < parents
    _swap(k, _parent(k));
    k = _parent(k);
  }
}

template <typename T>
void priority_queue<T>::_reheap_down(size_t k) {
  // helper function that move the item in the front of the priority queue
  // to keep the priority queue in a increase order

  // if k is already at the bottom of the tree, stop.
  if (_left_child(k) >= _size) return;
  else {
    size_t child = _left_child(k);

    // find the smallest of the two childs
    if ((_right_child(k) < _size) &&
        (_cmp(_data[_right_child(k)], _data[child]) < 0)) {
      child++;
    }

    // swap the child with the parent if child > parent, repeat until
    // the all value in the min-heap in an increasing order.
    if (_cmp(_data[k], _data[child]) > 0) {
      _swap(k, child);
      _reheap_down(child);
    }
  }
}

template <typename T>
void priority_queue<T>::_grow() {
  // double the capacity of the priority queue, while keeping all
  // the data of the original priority queue.

  _capacity *= 2; // double the capacity
  T *bigger_copy = new T[_capacity]; // built a new bigger queue

  // copy the data original priority queue into a bigger queue
  for(size_t i = 0; i < _size; i++){
    bigger_copy[i] = _data[i];
  }

  _data = bigger_copy; // save the new bigger queue
}
