#include <iostream>
#include <memory>
#include "Penguin.h"
using namespace std;

void doFly(Bird& b) {
    cout << b.getType() << endl;
    b.fly();
    cout << endl;
}

int main() {
    /* Declares a bird like normal. No inheritance is
      going on so this works exactly like you would expect */
    Bird b("albatross");
    cout << b.getType() << endl;
    b.fly();
    cout << endl;
    
    /* Declared a Penguin which inherits from Bird. Since
      Penguin inherits from Bird, all of Bird's member functions
      can be called. */
    Penguin p;
    cout << p.getType() << endl;
    p.fly();
    cout << endl;

    /* Since b is neither a reference nor a pointer to a Bird,
      Slicing will occur. This means that b will be interpreted
      at run time as a bird not a penguin so bird's fly will be
      called. */
    b = p;
    cout << b.getType() << endl;
    b.fly();
    cout << endl;
    
    /* To fix that problem, either make b a reference or a pointer
      as seen in the two examples below. See lecture 15 on RAII
      to see what shared_ptr is and how to use it. */
    shared_ptr<Bird> bPtr(new Penguin);
    cout << bPtr->getType() << endl;
    bPtr->fly();
    cout << endl;

    doFly(p);

    /* Dynamic cast will at run time determine the type and either return
      false or do the cast */
    Bird* bCast = new Penguin;
    if (dynamic_cast<Penguin*>(bCast)) {
        cout << "IT'S A PENGUIN!" << endl;
    }
    delete bCast;
}
