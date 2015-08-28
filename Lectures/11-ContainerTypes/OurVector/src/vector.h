#pragma once
// The idea of #pragma once is to make sure we don't run into problems with
// multiple includes of this header file. For exapmle, if we have:
//
//   #include <string>
//   #include <sstream>
//
// ... the <sstream> header itself includes <string> so by extension, we would
// have included <string> twice. If the <string> header didn't take any
// precautions, this would cause errors -- we would have defined the string
// class twice, for example. #pragma once prevents the file from being included
// more than once.

#include <string>

// Notice below that wherever we refer to string as std::string and size_t as
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

// Our Vector class is pretty simplistic at this point in time. It can only
// store strings, and has a host of problems that we haven't even encountered
// yet. However, it has the basic functionality of a dynamic array that grows as
// we need to store more and more elements.
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
  // refer to it as Vector::iterator. While inside the Vector's class
  // definition, we can just use iterator. Normally, iterators are implemented
  // as actual classes, but the details can become very complicated. Instead,
  // we'll take a shortcut and make iterator a nickname for a pointer to a
  // string. It serves the same purpose.
  typedef std::string* iterator;

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

  // at returns a reference to the string at the specified index. It returns a
  // reference so that we can use at for both reading and writing.
  std::string& at(std::size_t index);

  // capacity returns the number of elements the Vector can store before needing
  // to reallocate the underlying array. It is equivalent to the instance
  // variable, allocatedSize.
  std::size_t capacity();

  // reserve is a function we can call to guarantee that the underlying array
  // has an allocated size that is at least as large as minimum.
  void reserve(std::size_t minimum);

  // insert places the given string at the location specified by the position
  // iterator. It will shift all of the following elements over by one location.
  iterator insert(iterator position, std::string element);

  // push_back appends the given string to the end of the Vector.
  void push_back(std::string element);

private:
  // The private section of the Vector class contains implementation details
  // that clients shouldn't be concerned with. It details the actual mechanics
  // of how the Vector is represented, but these details should ideally be able
  // to change without breaking client code that uses our Vector.
  //
  // For that reason, we make these components private. The client never sees
  // the array pointer, so he/she never writes code which depends on that array
  // pointer.

  // elems is a pointer to the raw array containing the strings in the vector.
  std::string* elems;

  // logicalSize stores the number of elements the vector actually stores.
  std::size_t logicalSize;

  // allocatedSize stores the number of elements that can fit in the elems array
  // before it needs to be expanded.
  std::size_t allocatedSize;
};
