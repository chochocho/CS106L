#include "Vector.h"

#include <iostream>

using namespace std;

int main() {
    // Use our regular constructor
    Vector<int> a(10, 42);
    cout << "Constructor:" << endl;
    cout << a << endl;

    // Use our copy constructor
    Vector<int> b = a;
    cout << "Copy constructor:" << endl;
    cout << b << endl;

    // Use our copy assignment operator
    Vector<int> c;
    cout << "Copy Assignment" << endl;
    c = a;
    cout << c << endl;

    // Use our chained copy assignment operator. This example explains why the
    // copy assignment operator returns a reference to *this.
    cout << "Chained Assignment" << endl;
    // This next line is equivalent to a = (b = c)
    a = b = c;

    cout << a << endl;
    cout << b << endl;
    cout << c << endl;

    return 0;
}
