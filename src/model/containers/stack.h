#ifndef SRC_MODEL_CONTAINERS_STACK_H_
#define SRC_MODEL_CONTAINERS_STACK_H_

#include <iostream>

template <typename T>
class Stack {
 private:
  struct Node {
    T value;
    Node *next;
  };
  using value_type = T;
  using size_type = std::size_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  Node *ptr_;
  size_type size_ = 0;

  void DeleteStack();
  Stack &operator=(const Stack &s);
  void AllNumber(Node *bbb, T *buf_arr, const Stack &s);

 public:
  Stack();
  Stack(const Stack &s);
  Stack(Stack &&s);
  explicit Stack(std::initializer_list<value_type> const &items);
  ~Stack();

  void Push(const_reference value);
  void Pop();

  const_reference Peek() const { return ptr_->value; }
  reference Peek() { return ptr_->value; }
  bool Empty();
  size_type Size() const { return size_; }
  void Swap(Stack &other);

  void EmplaceFront() {}
  template <typename value_t, typename... Args>
  void EmplaceFront(value_t val, Args &&...args);
};

template <typename value_type>
Stack<value_type>::Stack() {
  ptr_ = nullptr;
}

template <typename value_type>
Stack<value_type>::Stack(const Stack &s) : ptr_(nullptr) {
  *this = s;
}

template <typename value_type>
Stack<value_type>::Stack(Stack &&s) : ptr_(nullptr) {
  DeleteStack();
  *this = s;
  s.DeleteStack();
}

template <typename value_type>
Stack<value_type>::Stack(std::initializer_list<value_type> const &items)
    : ptr_(nullptr) {
  for (auto element : items) {
    Push(element);
  }
}

template <typename value_type>
Stack<value_type>::~Stack() {
  DeleteStack();
}

template <typename value_type>
void Stack<value_type>::DeleteStack() {
  while (ptr_) {
    Node *buf = ptr_;
    ptr_ = ptr_->next;
    delete buf;
  }
  size_ = 0;
}

template <typename T>
void Stack<T>::Push(const_reference value) {
  if (ptr_) {
    Node *buf = new Node();
    buf->next = ptr_;
    buf->value = value;
    ptr_ = buf;
  } else {
    ptr_ = new Node();
    ptr_->value = value;
  }
  ++size_;
}

template <typename T>
void Stack<T>::Pop() {
  Node *buf = ptr_;
  if (ptr_) {
    ptr_ = ptr_->next;
    delete buf;
    --size_;
  }
}

template <typename value_type>
void Stack<value_type>::Swap(Stack &other) {
  Stack<value_type> buf_stack = other;
  other = *this;
  *this = buf_stack;
}

template <typename value_type>
bool Stack<value_type>::Empty() {
  bool empty = 1;
  if (ptr_) {
    empty = 0;
  }
  return empty;
}

template <typename value_type>
Stack<value_type> &Stack<value_type>::operator=(const Stack &s) {
  DeleteStack();
  Node *bbb = s.ptr_;
  value_type *buf_arr = new value_type[s.Size()]();
  AllNumber(bbb, buf_arr, s);
  for (size_type j = s.Size(); j > 0; --j) {
    Push(buf_arr[j - 1]);
  }
  delete[] buf_arr;
  return *this;
}

template <typename value_type>
void Stack<value_type>::AllNumber(Node *bbb, value_type *buf_arr,
                                  const Stack &s) {
  for (size_type i = 0; i < s.Size(); i++) {
    buf_arr[i] = bbb->value;
    bbb = bbb->next;
  }
}

template <typename value_type>
template <typename value_t, typename... Args>
void Stack<value_type>::EmplaceFront(value_t value, Args &&...args) {
  Push(value);
  EmplaceFront(args...);
}

#endif  // SRC_MODEL_CONTAINERS_STACK_H_
