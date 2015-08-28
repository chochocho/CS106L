#pragma once

#include <cstddef>
#include <algorithm>

/** Vector class definition **/

template <typename ElemType>
class Vector {
public:
  typedef ElemType* iterator;
  
  Vector();
  ~Vector();
  
  std::size_t size();
  bool empty();
  
  iterator begin();
  iterator end();
  
  ElemType& at(std::size_t index);
  ElemType& front();
  ElemType& back();
  
  std::size_t capacity();
  void reserve(std::size_t minimum);
  
  iterator insert(iterator position, ElemType element);
  iterator erase(iterator position);
  
  void push_back(ElemType element);
  
  void clear();

private:
  static const std::size_t kInitialSize = 4;
  
  // instance variables:
  ElemType* elems;
  std::size_t logicalSize;
  std::size_t allocatedSize;
};


/** Vector implementation details **/

template <typename ElemType>
Vector<ElemType>::Vector() {
  elems = new ElemType[kInitialSize];
  logicalSize = 0;
  allocatedSize = kInitialSize;
}

template <typename ElemType>
Vector<ElemType>::~Vector() {
  delete[] elems;
}

template <typename ElemType>
std::size_t Vector<ElemType>::size() {
  return logicalSize;
}

template <typename ElemType>
bool Vector<ElemType>::empty() {
  return size() == 0;
}

template <typename ElemType>
typename Vector<ElemType>::iterator Vector<ElemType>::begin() {
  return elems;
}

template <typename ElemType>
typename Vector<ElemType>::iterator Vector<ElemType>::end() {
  return begin() + size();
}

template <typename ElemType>
ElemType& Vector<ElemType>::at(std::size_t index) {
  return *(begin() + index);
}

template <typename ElemType>
ElemType& Vector<ElemType>::front() {
  return at(0);
}

template <typename ElemType>
ElemType& Vector<ElemType>::back() {
  return at(size() - 1);
}

template <typename ElemType>
std::size_t Vector<ElemType>::capacity() {
  return allocatedSize;
}

template <typename ElemType>
void Vector<ElemType>::reserve(std::size_t minimum) {
  if (allocatedSize < minimum) {
    do {
      allocatedSize *= 2;
    } while (allocatedSize < minimum);
    
    ElemType* newElems = new ElemType[capacity()];
    std::copy(begin(), end(), newElems);
    
    delete[] elems;
    elems = newElems;
  }
}

template <typename ElemType>
typename Vector<ElemType>::iterator Vector<ElemType>::insert(iterator position, ElemType element) {
  std::size_t index = position - begin();
  reserve(size() + 1);
  position = begin() + index;
  
  std::copy_backward(position, end(), end() + 1);
  
  *position = element;
  ++logicalSize;
  return position;
}

template <typename ElemType>
typename Vector<ElemType>::iterator Vector<ElemType>::erase(iterator position) {
  std::copy(position + 1, end(), position);
  --logicalSize;
  return position;
}

template <typename ElemType>
void Vector<ElemType>::push_back(ElemType element) {
  insert(end(), element);
}

template <typename ElemType>
void Vector<ElemType>::clear() {
  logicalSize = 0;
}
