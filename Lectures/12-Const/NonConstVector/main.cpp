#include "Vector.h"

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

template<typename T>
void PrintContainer(T& container) {
    // Since 'container' is a non-const parameter, this function could modify
    // its contents.  See the 'Vector' project for a const version of this
    // which solves this problem.
    typename T::iterator i = container.begin();
    for (; i != container.end(); ++i)
      cout << *i << endl;
}

int main() {
    Vector<int> numbers;
    for (int i = 0; i < 20; ++i)
      numbers.push_back(i * 10);

    PrintContainer(numbers);

    return 0;
}
