/******************************************************************************
  File:  Compression.cc
 
  Description: Built a priority queue base min heap. The priority queue have
               to have properties of a min heap such as all data are stored 
               in an array and is in the an increasing order as the indexing 
               down the list. The priority queue allows user to build a queue, 
               get the data at the front of the queue, size of the queue, add 
               item to and remove item from the queue.
 
 *****************************************************************************/

#ifndef PQ
#define PQ

template <typename T>
class priority_queue {
  // priority queue base min heap class

public:

  // initialize a priority-queue-base-min-heap and its properties
 priority_queue(int (*cmp)(const T &, const T &));

 // add new item into queue
 void add(const T & item);

 // remove the front item of the priority queue
 void remove();

 // return the first item in the priority queue
 T front() const;

 // return the size of the priority queue
 size_t size() const;

 private:

  size_t _capacity;                // capacity of the priority queue
  size_t _size;                    // amount of data is in the priority queue
  int (*_cmp)(const T &, const T &);  // _cmp is the comparison function
  T *_data;                        // array of data

  // helper member function:

  // wih the data at the given index, return its parent's index
  size_t _parent(size_t k);

  // with the data at the given index, return the index of its left child
  size_t _left_child(size_t k);

  // with the data at the given index, return the index of its right child
  size_t _right_child(size_t k);

  // swapping the values between two priority queues
  void _swap(size_t x, size_t y);

  // helper function that move the new added item up the priority queue
  // to keep the priority queue in a increase order
  void _reheap_up(size_t k);

  // helper function that move the item in the front of the priority queue
  // to keep the priority queue in a increase order
  void _reheap_down(size_t k);

  // double the capacity of the priority queue, while keeping all
  // the data of the original priority queue.
  void _grow();

};

#include "minheap.cc"

#endif
