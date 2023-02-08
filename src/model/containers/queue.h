#ifndef SRC_MODEL_CONTAINERS_QUEUE_H_
#define SRC_MODEL_CONTAINERS_QUEUE_H_
#include <iostream>

template <typename T>
class Queue {
 private:
  struct Node {
    T value;
    Node *next;
  };
  using value_type = T;
  using size_type = std::size_t;
  using reference = value_type &;
  using const_reference = const value_type &;

  size_type size_ = 0;
  Node *first_, *last_;
  void DeleteQueue();

 public:
  Queue();
  explicit Queue(std::initializer_list<value_type> const &items);
  Queue(const Queue &q);
  Queue(Queue &&q);
  ~Queue();
  Queue &operator=(Queue &&q);

  const_reference Front() const { return first_->value; }
  reference Front() { return first_->value; }
  const_reference Back() const { return last_->value; }
  reference Back() { return last_->value; }
  bool Empty();
  size_type Size() { return size_; }
  size_type Size() const { return size_; }

  void Push(const_reference value);
  void Pop();
  void Swap(Queue &other);
  void EmplaceBack() {}
  template <typename value, typename... Args>
  void EmplaceBack(value val, Args &&...args);
};

template <typename value_type>
Queue<value_type>::Queue() {
  first_ = nullptr;
  last_ = nullptr;
}

template <typename value_type>
Queue<value_type>::Queue(std::initializer_list<value_type> const &items)
    : first_(nullptr), last_(nullptr) {
  for (auto element : items) {
    Push(element);
  }
}

template <typename value_type>
Queue<value_type>::Queue(const Queue &q) : first_(nullptr), last_(nullptr) {
  DeleteQueue();
  Node *bbb = q.first_;
  for (size_type i = 0; i < q.Size(); ++i) {
    Push(bbb->value);
    bbb = bbb->next;
  }
}

template <typename value_type>
Queue<value_type>::Queue(Queue &&q) : first_(nullptr), last_(nullptr) {
  *this = std::move(q);
}

template <typename value_type>
Queue<value_type> &Queue<value_type>::operator=(Queue &&q) {
  DeleteQueue();
  Node *bbb = q.first_;
  for (size_type i = 0; i < q.Size(); ++i) {
    Push(bbb->value);
    bbb = bbb->next;
  }
  q.DeleteQueue();
  return *this;
}

template <typename value_type>
Queue<value_type>::~Queue() {
  DeleteQueue();
}

template <typename value_type>
void Queue<value_type>::DeleteQueue() {
  while (first_) {
    Node *buf = first_;
    first_ = first_->next;
    delete buf;
  }
  size_ = 0;
}

template <typename value_type>
bool Queue<value_type>::Empty() {
  bool empty = 1;
  if (first_) {
    empty = 0;
  }
  return empty;
}

template <typename value_type>
void Queue<value_type>::Push(const_reference value) {
  if (!first_) {
    first_ = new Node{value, nullptr};
    last_ = first_;
  } else {
    last_->next = new Node();
    last_ = last_->next;
    last_->value = value;
    last_->next = nullptr;
  }
  ++size_;
}

template <typename value_type>
void Queue<value_type>::Pop() {
  if (first_) {
    Node *buf = first_;
    first_ = first_->next;
    delete buf;
    --size_;
  }
}

template <typename value_type>
void Queue<value_type>::Swap(Queue &other) {
  Queue<value_type> buf_queue = std::move(other);
  for (; first_; Pop()) {
    other.Push(Front());
  }
  for (; buf_queue.first_; buf_queue.Pop()) {
    Push(buf_queue.Front());
  }
}

template <typename value_type>
template <typename value_t, typename... Args>
void Queue<value_type>::EmplaceBack(value_t value, Args &&...args) {
  Push(value);
  EmplaceBack(args...);
}

#endif  // SRC_MODEL_CONTAINERS_QUEUE_H_
