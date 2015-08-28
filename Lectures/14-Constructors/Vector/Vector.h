#pragma once

#include <cstddef>
#include <algorithm>
#include <ostream>

/** Vector class definition **/

template <typename ElemType>
class Vector {
public:
    typedef ElemType* iterator;
    typedef const ElemType* const_iterator;

    // We were able to write each of the three constructors using a single
    // constructor by using default values for our parameters. Specifying these
    // default values allows clients of the Vector class to leave certain
    // parameters out. If those arguments are omitted, they take on the specified
    // default value instead. The optional arguments must be omitted from right-
    // to-left; that is, we can leave out initialValue, or both initialValue and
    // initialSize, but we cannot leave out only initialSize.
    //
    // We declare the constructor explicit so that if the client happens to use
    // the one-argument constructor, it must be used explicitly. Otherwise, we
    // would be able to write code like the following:
    //
    //   Vector<int> myVector = 15;
    //
    // This would create a Vector of size 15, which is not at all what it looks
    // like the code is doing. To prevent clients from writing silly code like
    // this, we declare the constructor explicit.
    explicit Vector(size_t initialSize = 0, const ElemType& initialValue = ElemType());

    ~Vector();

    // We need to write a copy constructor in order to make sure that the Vector
    // class is copied correctly. The copy constructor is invoked whenever we
    // create a new Vector that's a copy of another:
    //
    //   Vector<int> a;
    //   Vector<int> b = a;
    //
    // It can also be invoked when we pass a Vector to another function by value,
    // or when we return a Vector from a function. If we don't bother implementing
    // the copy constructor, C++ will give us a default implementation that
    // initializes each of the new Vector's instance variables to be a copy of the
    // corresponding one in the "other" Vector.
    //
    // Sometimes this is sufficient, and we don't need to bother implementing it
    // ourselves. However, if the class needs to perform any resource management
    // (namely, does it have a pointer to memory that it allocates itself?), then
    // we'll need a copy constructor to make sure that data is copied properly.
    Vector(const Vector& other);

    // The copy assignment operator is declared just like any other operator, but
    // it has a special purpose.
    Vector& operator=(Vector other);

    size_t size() const;
    bool empty() const;

    const_iterator begin() const;
    const_iterator end() const;
    iterator begin();
    iterator end();

    const ElemType& at(size_t index) const;
    ElemType& at(size_t index);

    const ElemType& operator[](size_t index) const;
    ElemType& operator[](size_t index);

    const ElemType& front() const;
    const ElemType& back() const;
    ElemType& front();
    ElemType& back();

    size_t capacity() const;
    void reserve(size_t minimum);

    iterator insert(iterator position, const ElemType& element);
    iterator erase(iterator position);

    void push_back(const ElemType& element);

    void clear();

    // A very useful technique in making the implementation of the copy assignment
    // operator is called "copy-and-swap." See the implementation of the copy
    // assignment operator below for details.
    //
    // I decided to make this function public since other clients might find use
    // for it.
    void swap(Vector& other);

private:
    // instance variables:
    size_t logicalSize;
    size_t allocatedSize;
    ElemType* elems;
};

template <typename ElemType>
std::ostream& operator<<(std::ostream& output, const Vector<ElemType>& vec);

/** Vector implementation details **/

// When we actually write the implementation of the constructor, we can leave
// out the default values for the arguments as well as the explicit keyword.
template <typename ElemType>
Vector<ElemType>::Vector(size_t initialSize, const ElemType& initialValue)
    : logicalSize(initialSize)
    , allocatedSize(std::max(initialSize, size_t(4)))
    , elems(new ElemType[capacity()])
{
    // We need allocatedSize to be the maximum of these two values because it's
    // possible for initialSize to be 0. If we were to set allocatedSize to 0,
    // that would cause a lot of issues for us, particularly in the reserve
    // function.

    // The fill algorithm copies the specified value into each element in the
    // given range. Note that this function will do essentially nothing if
    // initialSize is zero, since begin() and end() are pointing to the same spot.
    std::fill(begin(), end(), initialValue);
}

template <typename ElemType>
Vector<ElemType>::~Vector() {
    delete[] elems;
}

// The copy constructor's actual implementation is pretty straightforward. We
// want to copy over all of the other Vector's data, but instead of directly
// copying its elems pointer, we'll make it a separate array of the same size
// and copy each of the individual elements over.
template <typename ElemType>
Vector<ElemType>::Vector(const Vector& other)
    : logicalSize(other.size())
    , allocatedSize(other.capacity())
    , elems(new ElemType[capacity()])
{
    std::copy(other.begin(), other.end(), begin());
}

// Normally, if we were to implement the copy assignment operator, it would look
// something like this (notice the overlap with the copy constructor):
//
//   if (this != &other) {
//     allocatedSize = other.capacity();
//     logicalSize = other.size();
//
//     delete[] elems;
//     elems = new ElemType[capacity()];
//     std::copy(other.begin(), other.end(), begin());
//   }
//
//   return *this;
//
// There are three main differences. First, the function must first free the
// memory originally owned by the Vector before elems is reassigned. Second, the
// function must ensure that self-assignment doesn't cause any problems. We do
// this by making sure that the this pointer is not equal to the address of the
// other Vector. Third, the function must return *this so that chaining
// assignments works.
//
// However, we can do a little better. If we implement the swap function,
// the copy constructor, and the destructor, we can use the code there to
// implement a fully functioning copy assignment operator. First, we make a
// temporary copy of the "other" Vector whose data we'll be copying. Then, we'll
// swap our data with the data in the temporary copy.
//
// Now, the current Vector has the same data as "other". When the function
// exits, the temporary copy goes out of scope and the Vector destructor cleans
// up the memory it contains. This is the final step which ensures that our old
// memory is not leaked.
template <typename ElemType>
Vector<ElemType>& Vector<ElemType>::operator=(Vector other) {
    swap(other);
    return *this;
}

template <typename ElemType>
size_t Vector<ElemType>::size() const {
    return logicalSize;
}

template <typename ElemType>
bool Vector<ElemType>::empty() const {
    return size() == 0;
}

template <typename ElemType>
typename Vector<ElemType>::const_iterator Vector<ElemType>::begin() const {
    return elems;
}

template <typename ElemType>
typename Vector<ElemType>::iterator Vector<ElemType>::begin() {
    return elems;
}

template <typename ElemType>
typename Vector<ElemType>::const_iterator Vector<ElemType>::end() const {
    return begin() + size();
}

template <typename ElemType>
typename Vector<ElemType>::iterator Vector<ElemType>::end() {
    return begin() + size();
}

template <typename ElemType>
const ElemType& Vector<ElemType>::at(size_t index) const {
    return *(begin() + index);
}

template <typename ElemType>
ElemType& Vector<ElemType>::at(size_t index) {
    return *(begin() + index);
}

template <typename ElemType>
const ElemType& Vector<ElemType>::operator[](size_t index) const {
    return at(index);
}

template <typename ElemType>
ElemType& Vector<ElemType>::operator[](size_t index) {
    return at(index);
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
size_t Vector<ElemType>::capacity() const {
    return allocatedSize;
}

template <typename ElemType>
void Vector<ElemType>::reserve(size_t minimum) {
    if (allocatedSize < minimum) {
        while (allocatedSize < minimum)
            allocatedSize *= 2;

        ElemType* newElems = new ElemType[capacity()];
        std::copy(begin(), end(), newElems);

        delete[] elems;
        elems = newElems;
    }
}

template <typename ElemType>
typename Vector<ElemType>::iterator Vector<ElemType>::insert(iterator position, const ElemType& element) {
    size_t index = position - begin();
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
void Vector<ElemType>::push_back(const ElemType& element) {
    insert(end(), element);
}

template <typename ElemType>
void Vector<ElemType>::clear() {
    logicalSize = 0;
}

// swap is pretty straightforward, since we can just use the STL algorithm
// std::swap to swap the individual instance variables in the Vector.
template <typename ElemType>
void Vector<ElemType>::swap(Vector& other) {
    std::swap(logicalSize, other.logicalSize);
    std::swap(allocatedSize, other.allocatedSize);
    std::swap(elems, other.elems);
}

template <typename ElemType>
std::ostream& operator<<(std::ostream& output, const Vector<ElemType>& vec) {
    output << "[ ";
    for (size_t i = 0; i < vec.size(); ++i)
        output << vec[i] << ' ';
    output << "]";
    return output;
}
