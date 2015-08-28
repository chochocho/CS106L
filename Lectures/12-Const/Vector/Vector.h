#pragma once

#include <cstddef>
#include <algorithm>

/** Vector class definition **/

template <typename ElemType>
class Vector {
public:
    // We introduce a new type: const_iterator. The const_iterator is an iterator
    // that is allowed to read from the underlying container, but cannot be used
    // to write to it. This allows us to use iterators on const Vectors, since
    // only read-only operations are allowed.
    //
    // The type is const ElemType* -- this can be read as a pointer to a const
    // ElemType (i.e. ElemType object that is read-only). This means the pointer
    // itself is not const, and can be reassigned, incremented, etc.
    typedef ElemType* iterator;
    typedef const ElemType* const_iterator;

    Vector();
    ~Vector();

    // size and empty are const member functions. They are declared as such
    // because both are read-only functions -- calling .size() on a vector won't
    // change any of its contents (one would hope). We need to explicitly state
    // that it's const, though, in order for code which uses the Vector to work
    // properly.
    size_t size() const;
    bool empty() const;

    // We need two different versions of begin and end. The one declared const is
    // read-only -- it returns a const_iterator, which is a read-only iterator.
    const_iterator begin() const;
    const_iterator end() const;

    // The compiler is able to differentiate between which one is being called
    // through a process called "const overload resolution." Even though this
    // non-const version of begin and the const version above have exactly the
    // same name and parameter lists, the compiler still always knows which one to
    // call. The const version is called if begin is invoked on a const Vector;
    // otherwise, the non-const version is called.
    iterator begin();
    iterator end();

    // Like with begin and end, at must be const overloaded in order to support
    // read-only access in addition to read/write access.
    const ElemType& at(size_t index) const;
    ElemType& at(size_t index);

    // Like with at, front and back need to be const overloaded.
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
    static const size_t kInitialSize = 4;
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
    // This is called the "const cast trick." Notice that the implementation of
    // both versions of .at(...) are identical. To avoid code duplication, we
    // would like one version to call the other. We will have the non-const
    // version call the const version, since that doesn't break any const
    // guarantees (calling the other way around actually does).
    //
    // In order to get the right version to be invoked, we need to call .at(...)
    // on a const reference to ourself. The resulting type is const ElemType&, but
    // we want to return an ElemType&, so we need to strip the const away using a
    // const_cast. This is normally a dangerous procedure, but in this case, we
    // know that we added that const-ness on in the first place, so it's safe.
    const Vector& constThis = *this;
    return const_cast<ElemType&>(constThis.at(index));
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
