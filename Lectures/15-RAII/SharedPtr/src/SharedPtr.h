#pragma once

#include <cstdlib>

// The SharedPtr class is what we call a smart pointer. The class provides a
// wrapper around a raw pointer to some data. The advantage to creating this
// class is that we can implement the destructor to automatically clean up the
// acquired memory, taking that burden away from the programmer.
template <typename ElemType>
class SharedPtr {
public:
  // We can initialize the SharedPtr with a pointer. If we don't, then it will
  // be default initialized to point to NULL.
  SharedPtr(ElemType* data = NULL);
  ~SharedPtr();
  
  // We need to make sure that the SharedPtr copies correctly. If we use default
  // copying behavior, the underlying resource will be freed for every SharedPtr
  // which is pointing to it, which would cause a host of memory-related errors.
  SharedPtr(const SharedPtr& other);
  SharedPtr& operator=(const SharedPtr& other);
  
  // The SharedPtr class should mimic the behavior of regular pointers. We can
  // accomplish this by implementing various operators: *, ->, ==, and !=.
  ElemType& operator*() const;
  ElemType* operator->() const;
  
  bool operator==(const SharedPtr& other) const;
  bool operator!=(const SharedPtr& other) const;
  
  // We may want to give the client a means of accessing the underlying pointer
  // or the reference count.
  ElemType* ptr() const;
  int ref_count() const;

private:
  // Each SharedPtr object keeps track of the actual data it's pointing to, as
  // well as the number of SharedPtr objects which are pointing to that data.
  // This ensures that the data is only freed when it needs to be freed.
  ElemType* resource;
  int* refCount;
  
  // attach and detach are helper functions which handle sharing the same data
  // as a given SharedPtr object, and "unsharing" from that data.
  void attach(const SharedPtr& other);
  void detach();
};

template <typename ElemType>
SharedPtr<ElemType>::SharedPtr(ElemType* data) 
  : resource(data)
  , refCount(new int (1))
{
  // Empty
}

template <typename ElemType>
SharedPtr<ElemType>::~SharedPtr() {
  detach();
}

template <typename ElemType>
SharedPtr<ElemType>::SharedPtr(const SharedPtr& other) {
  attach(other);
}

template <typename ElemType>
SharedPtr<ElemType>& SharedPtr<ElemType>::operator=(const SharedPtr& other) {
  if (this != &other) {
    // First, we should no longer point to the old data. Then, re-attach to the
    // new data.
    detach();
    attach(other);
  }
  
  return *this;
}

template <typename ElemType>
ElemType& SharedPtr<ElemType>::operator*() const {
  return *resource;
}

template <typename ElemType>
ElemType* SharedPtr<ElemType>::operator->() const {
  // Equivalently, we could just return resource. See the notes for lecture 13
  // for why &**this does the same thing.
  return &**this;
}

template <typename ElemType>
bool SharedPtr<ElemType>::operator==(const SharedPtr& other) const {
  return resource == other.resource;
}

template <typename ElemType>
bool SharedPtr<ElemType>::operator!=(const SharedPtr& other) const {
  return !(*this == other);
}

template <typename ElemType>
ElemType* SharedPtr<ElemType>::ptr() const {
  return resource;
}

template <typename ElemType>
int SharedPtr<ElemType>::ref_count() const {
  return *refCount;
}

template <typename ElemType>
void SharedPtr<ElemType>::attach(const SharedPtr& other) {
  resource = other.resource;
  refCount = other.refCount;
  ++(*refCount);
}

template <typename ElemType>
void SharedPtr<ElemType>::detach() {
  --(*refCount);
  if (*refCount == 0) {
    delete resource;
    delete refCount;
  }
}






