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

    Vector();
    ~Vector();

    size_t size() const;
    bool empty() const;

    const_iterator begin() const;
    const_iterator end() const;

    iterator begin();
    iterator end();

    const ElemType& at(size_t index) const;
    ElemType& at(size_t index);

    // The interface declaration for the [] notation follows the format for all
    // operators being overloaded: we use the keyword 'operator' and the actual
    // operator being implemented. Just like with .at(...), we need two versions
    // so that both const and non-const Vectors can use operator[].
    const ElemType& operator[](size_t index) const;
    ElemType& operator[](size_t index);

    const ElemType& front() const;
    ElemType& front();

    const ElemType& back() const;
    ElemType& back();

    size_t capacity() const;
    void reserve(size_t minimum);

    iterator insert(iterator position, const ElemType& element);
    iterator erase(iterator position);

    void push_back(const ElemType& element);

    void clear();

private:
    // instance variables:
    ElemType* elems;
    size_t logicalSize;
    size_t allocatedSize;
};

// We declare our overloading of operator<< here as a "free function" rather
// than as a "member function". A member function, also known as a "method", is
// a function that is invoked on an object, such as .size() on a string. A free
// function, on the other hand, is just invoked with its parameters, such as the
// sqrt function in the math library.
//
// We need to make operator<< a free function because if we tried to make it a
// member function, that would place the Vector as the left-hand argument,
// forcing us to write code like this:
//
//   myVector << cout;
//
// Since this goes against convention, we write it as a free function instead.
// The function returns an ostream object by reference -- the same ostream
// object that was passed in -- so that we can chain the << operation together:
//
//   cout << myVector << endl;
//   operator(operator(cout, myVector), endl);
template <typename ElemType>
std::ostream& operator<<(std::ostream& output, const Vector<ElemType>& vec);

/** Vector implementation details **/

// kInitialSize is a constant that controls the initial allocated size of the
// Vector.
const size_t kInitialSize = 4;

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
const ElemType& Vector<ElemType>::front() const {
    return at(0);
}

template <typename ElemType>
ElemType& Vector<ElemType>::front() {
    return at(0);
}

template <typename ElemType>
const ElemType& Vector<ElemType>::back() const {
    return at(size() - 1);
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

template <typename ElemType>
std::ostream& operator<<(std::ostream& output, const Vector<ElemType>& vec) {
    output << "[ ";
    for (size_t i = 0; i < vec.size(); ++i)
        output << vec[i] << ' ';
    output << "]";
    return output;
}
