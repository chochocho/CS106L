#include <iostream>
using namespace std;

// Let's say we initialize the data of this class not with a constructor, but
// with a special member function that we name 'init'
class foo {
public:
    int value;
    void init(int initialValue);
    const int constValue;
};

void foo::init(int initialValue) {
    value = initialValue;

    // We can't initialize the constant member variable here!  To the compiler,
    // this looks like we're trying to modify a const variable instead of
    // initializing it, so it (correctly) rejects this code as invalid.

    /*
       constValue = initialValue;
       */
}


int main() {
    // Because we didn't write our own default constructor, x.value is going to
    // start out with garbage data in it
    foo x;

    // Oops, looks like we forgot to call our special init function!
    // x.init();

    // The value printed could be anything
    cout << x.value << endl;
}
