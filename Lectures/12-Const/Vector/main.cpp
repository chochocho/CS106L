#include "Vector.h"

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

// We would like to be able to pass our Vector into this function by reference
// for efficiency purposes. However, we don't want PrintVector to inadvertently
// change the Vector. The solution is to pass it in by reference-to-const.
template<typename T>
void PrintContainer(const T& container) {
    // We only use .size() and .at(...) on the Vector. .size() is always a read-
    // only function, so that's totally fine on a const Vector. .at(...) can be
    // used both for reading and for writing, so we need to modify the Vector
    // class interface to make a distinction. Here, we are using a version that
    // only allows for reading. If we were to try to assign something to .at(...),
    // we would encounter a compiler error.
    typename T::const_iterator i = container.begin();
    for (; i != container.end(); ++i)
      cout << *i << endl;
}

int main() {
    Vector<int> numbers;
    for (int i = 0; i < 20; ++i)
      numbers.push_back(i * 10);

    // Outside, here, where the Vector is not declared const, we are using a
    // different version of .at(...) - the one that allows for both reading and
    // writing.
    numbers.at(0) = 10;
    PrintContainer(numbers);

    return 0;
}
