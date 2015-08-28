#include "SharedPtr.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
  // Instead of declaring strPtr as a raw pointer (string*), we'll make it a
  // SharedPtr object. The idea is that the SharedPtr should look and act just
  // like a regular pointer, except that it'll automatically handle memory
  // management for us.
  SharedPtr<string> strPtr = new string("Release the hounds!");
  cout << *strPtr << endl;
  cout << "There are " << strPtr->size() << " characters." << endl;
  
  // We need to make sure that the pointer copies correctly. See SharedPtr.h for
  // details on how this is handled.
  SharedPtr<string> strPtrCopy = strPtr;
  cout << *strPtrCopy << endl;
  
  return 0;
}
