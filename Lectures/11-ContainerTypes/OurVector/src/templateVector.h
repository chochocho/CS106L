#pragma once
// The idea of #pragma once is to make sure we don't run into problems with
// multiple includes of this header file. For exapmle, if we have:
//
//   #include <string>
//   #include <sstream>
//
// ... the <sstream> header itself includes <ValueType> so by extension, we would
// have included <ValueType> twice. If the <ValueType> header didn't take any
// precautions, this would cause errors -- we would have defined the ValueType
// class twice, for example. #pragma once prevents the file from being included
// more than once.

#include <algorithm>
using namespace std;

// Notice below that wherever we refer to size_t as
// std::size_t. These are the full names for these types, since they are located
// in the standard library. Normally, we don't have to type out the std:: prefix
// because we use the line:
//
//   using namespace std;
//
// However, it is considered very bad practice to have this line in a header
// file. The reason is that other code will #include this file. By extension,
// everything that includes this header will automatically be forced to have the
// same line, which can introduce compiler errors due to naming conflicts.

// Our simplistic Vector class from before has been expanded to be able to hold 
// any value type. Notice the template <typename ValueType> above the class
// declaration which says that the class is templatized.
template <typename ValueType>
class Vector {
public:
  // We have implemented the following:
  // - constructor, destructor
  // - size, empty
  // - begin, end (iterators)
  // - at
  // - reserve, capacity
  // - insert
  // - push_back

  // Other things to consider implementing:
  // - erase
  // - resize
  // - clear
  // - front, back

  // The iterator type is nested within the Vector class. Outside, we would
  // refer to it as Vector<ValueType>::iterator. While inside the Vector's class
  // definition, we can just use iterator. Normally, iterators are implemented
  // as actual classes, but the details can become very complicated. Instead,
  // we'll take a shortcut and make iterator a nickname for a pointer to a
  // ValueType. It serves the same purpose.
  typedef ValueType* iterator;

  // The Vector constructor initializes the state of a Vector. It is invoked
  // whenever a client creates a new Vector object.
  Vector();

  // The Vector destructor cleans up any resources that the Vector class used.
  // This includes dynamically allocated memory, which our Vector uses. Note
  // that you should never call ~Vector() explicitly. It is automatically called
  // whenever a Vector object is destroyed, whether automatically when it goes
  // out of scope or manually when you call delete on a pointer to a Vector.
  ~Vector();

  // size simply returns how many items the Vector is storing. It is equivalent
  // to the instance variable, logicalSize.
  std::size_t size();

  // empty returns true if and only if the Vector has no elements.
  bool empty();

  // begin and end return iterators for our Vector. begin is an iterator
  // pointing at the first element in the Vector, while end is an iterator
  // pointing one spot past the last element in the Vector.
  iterator begin();
  iterator end();

  // at returns a reference to the ValueType at the specified index. It returns a
  // reference so that we can use at for both reading and writing.
  ValueType& at(std::size_t index);

  // capacity returns the number of elements the Vector can store before needing
  // to reallocate the underlying array. It is equivalent to the instance
  // variable, allocatedSize.
  std::size_t capacity();

  // reserve is a function we can call to guarantee that the underlying array
  // has an allocated size that is at least as large as minimum.
  void reserve(std::size_t minimum);

  // insert places the given ValueType at the location specified by the position
  // iterator. It will shift all of the following elements over by one location.
  iterator insert(iterator position, ValueType element);

  // push_back appends the given ValueType to the end of the Vector.
  void push_back(ValueType element);

private:
  // The private section of the Vector class contains implementation details
  // that clients shouldn't be concerned with. It details the actual mechanics
  // of how the Vector is represented, but these details should ideally be able
  // to change without breaking client code that uses our Vector.
  //
  // For that reason, we make these components private. The client never sees
  // the array pointer, so he/she never writes code which depends on that array
  // pointer.

  // elems is a pointer to the raw array containing the ValueTypes in the vector.
  ValueType* elems;

  // logicalSize stores the number of elements the vector actually stores.
  std::size_t logicalSize;

  // allocatedSize stores the number of elements that can fit in the elems array
  // before it needs to be expanded.
  std::size_t allocatedSize;
};

// kInitialSize is a constant that controls the initial allocated size of the
// Vector.
static const size_t kInitialSize = 4;

// Since the vector is now templatized, the template <typename ValueType>
// is now needed above every function definition
template <typename ValueType>
Vector<ValueType>::Vector() {
  elems = new ValueType[kInitialSize];
  logicalSize = 0;
  allocatedSize = kInitialSize;
}

template <typename ValueType>
Vector<ValueType>::~Vector() {
  delete[] elems;
}

template <typename ValueType>
size_t Vector<ValueType>::size() {
  return logicalSize;
}

template <typename ValueType>
bool Vector<ValueType>::empty() {
  // We refer to the size of the Vector using size() rather than logicalSize.
  // Even though they're the same thing, we should prefer to use the public
  // interface of the Vector over its private interface, whenever possible. This
  // ensures that even if the private implementation details of Vector change,
  // this function will still do its job correctly.
  return size() == 0;
}

// When refering to an inner type of a template type (in this case the 
// iterator), it necessary to add an extra typename before listing the 
// type so instead of Vector<ValueType>::iterator we now have
// typename Vector<ValueType>::iterator
template <typename ValueType>
typename Vector<ValueType>::iterator Vector<ValueType>::begin() {
  return elems;
}

template <typename ValueType>
typename Vector<ValueType>::iterator Vector<ValueType>::end() {
  // Like empty(), we can implement end() using just the public interface.
  // begin() gives us a pointer to the first element in the array, while size()
  // is the number of elements total. Shifting begin() over by size() thus gives
  // a pointer to the location which is one spot past the last actual element in
  // the array, which is what end() should return.
  return begin() + size();
}

template <typename ValueType>
ValueType& Vector<ValueType>::at(size_t index) {
  // This is equivalent to using elems[index].
  return *(begin() + index);
}

template <typename ValueType>
size_t Vector<ValueType>::capacity() {
  return allocatedSize;
}

template <typename ValueType>
void Vector<ValueType>::reserve(size_t minimum) {
  // If our array is already large enough, do nothing.
  if (allocatedSize < minimum) {
    // Keep doubling the allocated size until it's large enough:
    while (allocatedSize < minimum)
      allocatedSize *= 2;

    // Allocate a new array of the appropriate size and copy over the existing
    // elements of the vector:
    ValueType* newElems = new ValueType[capacity()];
    copy(begin(), end(), newElems);

    // Delete the old array and assign our elems pointer to the new one:
    delete[] elems;
    elems = newElems;
  }
}

template <typename ValueType>
typename Vector<ValueType>::iterator Vector<ValueType>::insert(iterator position, ValueType element) {
  // We need to store the index of the iterator since reserve might invalidate
  // it. In particular, if reserve ends up allocating a new array, then position
  // will be pointing into the old array (which is no longer valid memory). Once
  // reserve has finished executing, we can readjust position.
  size_t index = position - begin();
  reserve(size() + 1);
  position = begin() + index;

  // Shift everything from position to the end over by one spot:
  //copy(position, end(), position + 1); // BEWARE, BUG BE HERE
  copy_backward(position, end(), end() + 1); // No bug version

  // Write our element into the appropriate location and update the Vector:
  *position = element;
  ++logicalSize;
  return position;
}

template <typename ValueType>
void Vector<ValueType>::push_back(ValueType element) {
  insert(end(), element);
}
