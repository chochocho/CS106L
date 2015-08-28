#include <iostream>
using namespace std;

// This file demonstrates the WRONG way to read two numbers from a stream.  The
// complexity associated with this is why Stanford provides simpio.h and the
// getInteger function.
int getInteger() {
  cout << "Please enter an integer value" << endl;
  int value;
  while (true) {
    cin >> value;
    if (!cin.fail()) break;

    cout << "Please re-enter an integer value: " << endl;
  }
  return value;
}


int main() {
  // Say that the user enters the number 867.5309 here.  The stream will read
  // "867", and return that as the integer result.
  cout << "The first value was: " << getInteger() << endl;

  // The string ".5309" will remain at the end of the stream, so whatever the
  // user enters here will fail to be read, because "." isn't part of any valid
  // integer
  cout << "The second value was: " << getInteger() << endl;
}
