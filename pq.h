 /* The code provided by Professor Alistair Campbell */

#ifndef PQ
#define PQ

template <typename T>
class priority_queue {
 private:
  struct node {
    T data;
    node *next;
    node(const T &, node *);
  };
  int (*_cmp)(const T &, const T &);  // _cmp is the comparison function
  node *_front;
  size_t _size;

  // helper member function:
  void _add_helper(const T &, node * &);

 public:
  priority_queue(int (*cmp)(const T &, const T &));
  void add(const T & item);
  void remove();
  T front() const;
  size_t size() const;
};

#include "pq.cc"

#endif
