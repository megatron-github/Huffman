/* The code provided by Professor Alistair Campbell */

template <typename T>
priority_queue<T>::priority_queue(int (*cmp)(const T &, const T &))
{
  _front = NULL;
  _size = 0;
  _cmp = cmp;
}

template <typename T>
priority_queue<T>::node::node(const T & item, node * rest)
  : data(item), next(rest) {}

template <typename T>
void priority_queue<T>::_add_helper(const T & item, node * & lst)
{
  if (lst == NULL)
    lst = new node(item, NULL);
  else if (_cmp(item, lst->data) <= 0)
    lst = new node(item, lst);
  else _add_helper(item, lst->next);
}

template <typename T>
void priority_queue<T>::add(const T & item)
{

  _add_helper(item, _front);
  _size++;
}

template <typename T>
void priority_queue<T>::remove()
{
  node * dead = _front;
  _front = _front->next;
  delete dead;
  _size--;
}

template <typename T>
T priority_queue<T>::front() const
{
  return _front->data;
}

template <typename T>
size_t priority_queue<T>::size() const
{
  return _size;
}
