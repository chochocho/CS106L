// Note: see the comments in Vector.h for detailed descriptions of what each
// function is supposed to do.
#include "vector.h"

#include <algorithm>

// using namespace std; is more acceptable in a .cpp file, since no other
// files will #include this .cpp. Some people still believe that using namespace
// should be avoided altogether, but we include it for convenience.
using namespace std;

// kInitialSize is a constant that controls the initial allocated size of the
// Vector.
static const size_t kInitialSize = 4;

Vector::Vector() {
  elems = new string[kInitialSize];
  logicalSize = 0;
  allocatedSize = kInitialSize;
}

Vector::~Vector() {
  delete[] elems;
}

size_t Vector::size() {
  return logicalSize;
}

bool Vector::empty() {
  // We refer to the size of the Vector using size() rather than logicalSize.
  // Even though they're the same thing, we should prefer to use the public
  // interface of the Vector over its private interface, whenever possible. This
  // ensures that even if the private implementation details of Vector change,
  // this function will still do its job correctly.
  return size() == 0;
}

Vector::iterator Vector::begin() {
  return elems;
}

Vector::iterator Vector::end() {
  // Like empty(), we can implement end() using just the public interface.
  // begin() gives us a pointer to the first element in the array, while size()
  // is the number of elements total. Shifting begin() over by size() thus gives
  // a pointer to the location which is one spot past the last actual element in
  // the array, which is what end() should return.
  return begin() + size();
}

string& Vector::at(size_t index) {
  // This is equivalent to using elems[index].
  return *(begin() + index);
}

size_t Vector::capacity() {
  return allocatedSize;
}

void Vector::reserve(size_t minimum) {
  // If our array is already large enough, do nothing.
  if (allocatedSize < minimum) {
    // Keep doubling the allocated size until it's large enough:
    while (allocatedSize < minimum)
      allocatedSize *= 2;

    // Allocate a new array of the appropriate size and copy over the existing
    // elements of the vector:
    string* newElems = new string[capacity()];
    copy(begin(), end(), newElems);

    // Delete the old array and assign our elems pointer to the new one:
    delete[] elems;
    elems = newElems;
  }
}

Vector::iterator Vector::insert(iterator position, string element) {
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

void Vector::push_back(string element) {
  insert(end(), element);
}
