#pragma once

#include <cstdlib> //for definition of NULL

// The LinkedList class represents a list of elements stored internally as a
// linked list. It's a very bare class that only supports insertion and
// iteration, but we use it to demonstrate operator overloading for the
// associated iterator clas.
template <typename ElemType>
class LinkedList {
public:
    // const_iterator is declared here as a class that's nested within the
    // LinkedList class. We'll flesh the definition of its body later on.
    class const_iterator;

    LinkedList();
    ~LinkedList();

    void insert(const ElemType& value);

    const_iterator begin() const;
    const_iterator end() const;

private:
    // The ListCell struct represents how we internally store the elements in the
    // linked list. Each element is in its own cell, and each cell has a link to
    // the next cell.
    struct ListCell {
        ElemType value;
        ListCell* next;
    };

    // We keep a pointer to both the head and the tail of the linked list in order
    // to offer both iteration and insertion.
    ListCell* head;
    ListCell* tail;

    // The const_iterator class needs to be able to have access to the LinkedList
    // class's implementation details in order to work properly. In particular,
    // operator++ needs to make the iterator follow a particular element's next
    // pointer to the next cell. ListCell is declared private in the LinkedList
    // class, so the only way that const_iterator can access it is by declaring
    // the const_iterator to be a friend.
    friend class const_iterator;
};

// const_iterator (nested within LinkedList) is actually defined here. We would
// normally probably just declare the member functions of const_iterator here
// and define their implementations later on, but for the ease of following the
// code, I'll place the entire implementation in the class declaration.
template <typename ElemType>
class LinkedList<ElemType>::const_iterator {
public:
    // operator* returns a reference to the actual value in the linked list that
    // the iterator is currently looking at.
    const ElemType& operator*() {
        return curr->value;
    }

    // In C++, operator-> is implemented by applying -> to whatever is returned by
    // the function. That means that operator-> is interpreted as follows:
    //
    //   const_iterator itr; // initialize this somehow...
    //   cout << itr->size() << endl;
    //   cout << (itr.operator->())->size();
    //
    // As a result, operator-> should almost always return a pointer to whatever
    // type is returned by operator*. Our implementation which returns &**this
    // guarantees that this is the case -- it returns the address of **this, which
    // is the application of operator* to the current object (*this).
    const ElemType* operator->() {
        return &**this;
    }

    // This version of operator++ is the pre-increment version, which returns the
    // new value of the iterator object after the increment takes place. The
    // implementation is relatively straightforward as a result since we can just
    // return the object as it is by the end of the function.
    const_iterator& operator++() {
        curr = curr->next;
        return *this;
    }

    // This version of operator++ is the post-increment version, which returns the
    // old value of the iterator object before the increment takes place. The int
    // parameter is a dummy parameter that is used by the compiler to distinguish
    // between the two different types of increment. No int is every actually
    // passed in when the function is called, since it's invoked as either:
    //
    //   itr++; // OR
    //   ++itr;
    //
    // pre-increment is almost always more efficient than post-increment since
    // post-increment must return the old value of the iterator, which no longer
    // exists. As a result, what it returns must be copy of the iterator that it
    // makes before the increment takes place.
    const_iterator operator++(int dummy) {
        const_iterator old = *this;
        ++(*this);
        return old;
    }

    // operator== simply returns true if this current iterator is equal to the one
    // that is passed int.
    bool operator==(const const_iterator& other) {
        return curr == other.curr;
    }

private:
    // curr represents the linked list cell that the iterator is currently looking
    // at. In order to use this, we had to declare the const_iterator class as a
    // friend of the LinkedList class.
    ListCell* curr;

    // We must also declare LinkedList to be a friend of the const_iterator class,
    // because LinkedList will later access the private members of const_iterator.
    // Specifically, LinkedList will set curr in the iterators that it creates in
    // the .begin() and .end() functions (see below).
    friend class LinkedList;
};

template <typename ElemType>
LinkedList<ElemType>::LinkedList() {
    head = tail = NULL;
}

template <typename ElemType>
LinkedList<ElemType>::~LinkedList() {
    while (head != NULL) {
        ListCell* next = head->next;
        delete head;
        head = next;
    }
}

template <typename ElemType>
void LinkedList<ElemType>::insert(const ElemType& value) {
    ListCell* newCell = new ListCell;
    newCell->value = value;
    newCell->next = NULL;
    if (head == NULL) {
        head = tail = newCell;
    } else {
        tail->next = newCell;
        tail = newCell;
    }
}

template <typename ElemType>
typename LinkedList<ElemType>::const_iterator LinkedList<ElemType>::begin() const {
    const_iterator itr;
    itr.curr = head;
    return itr;
}

template <typename ElemType>
typename LinkedList<ElemType>::const_iterator LinkedList<ElemType>::end() const {
    const_iterator itr;
    itr.curr = NULL;
    return itr;
}
